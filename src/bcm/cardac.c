/* 
 * ASoC Driver for CarDAC
 * 
 * Author:  Karthik Karyamapudi <karthikkaryamapudi@gmail.com>
 * Based on the TauDAC Driver by Sergej Sawazki
 * Based on the HifiBerry Digi Driver by Daniel Matuschek
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 */

#include <linux/module.h>
#include <linux/platform_device.h>

#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/pcm_params.h>
#include <sound/soc.h>
#include <linux/gpio/consumer.h>
#include <linux/clk.h>

#include "../codecs/tas6424.h"

static struct gpio_desc *cardac_clksel_gpio;
static struct clk	*cardac_mclk;
static struct clk 	*cardac_plld;

static int cardac_hw_params(struct snd_pcm_substream *substream, struct snd_pcm_hw_params *params){
    struct snd_soc_pcm_runtime *rtd = substream->private_data;
    struct snd_soc_dai *codec_dai = rtd->codec_dai;
    struct snd_soc_codec *codec = rtd->codec;
    struct snd_soc_dai *cpu_dai = rtd->cpu_dai;
    
    int samplerate = params_rate(params);
    
    switch(samplerate){
        case 44100:
            gpiod_set_value_cansleep(cardac_clksel_gpio, 1);
        case 48000:
            gpiod_set_value_cansleep(cardac_clksel_gpio, 0);
        default:
            dev_err(codec->dev, "Failed to set clock rate - unsupported sample rate");
    }
    
    snd_soc_dai_set_fmt(codec_dai, SND_SOC_DAIFMT_CBS_CFS|SND_SOC_DAIFMT_I2S);
    snd_soc_dai_set_fmt(cpu_dai, SND_SOC_DAIFMT_CBS_CFS|SND_SOC_DAIFMT_I2S);
    
    return snd_soc_dai_set_bclk_ratio(cpu_dai,64);
}

/* machine stream operations */
static struct snd_soc_ops cardac_ops = {
	.hw_params = cardac_hw_params,
};

static struct snd_soc_dai_link cardac_dai[] = {
{
	.name		= "Cardac",
	.stream_name	= "Cardac i2s Stream",
	.cpu_dai_name	= "bcm2835-i2s.0",
	.codec_dai_name	= "tas6424-amplifier",
	.platform_name	= "bcm2835-i2s.0",
	.codec_name	= "tas6424",
/*	.dai_fmt	= SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
				SND_SOC_DAIFMT_CBM_CFM,
*/	.ops		= &cardac_ops,
},
};

/* audio machine driver */
static struct snd_soc_card cardac_card = {
	.name         = "snd_cardac",
	.driver_name  = "CarDAC",
	.owner        = THIS_MODULE,
	.dai_link     = cardac_dai,
	.num_links    = ARRAY_SIZE(cardac_dai),
};



static int cardac_probe(struct platform_device *pdev){
    int ret;
    struct device_node *np;
    struct device_node *i2s_node;
    cardac_card.dev = &pdev->dev;
    struct snd_soc_dai_link *dai = &cardac_dai[0];
    struct device_node *codec_node;
    
    np = pdev->dev.of_node;
    if (np == NULL) {
        dev_err(&pdev->dev, "Device tree node not found\n");
        return ENODEV;
    }
    i2s_node = of_parse_phandle(pdev->dev.of_node,
					"i2s-controller", 0);
    codec_node = of_parse_phandle(pdev->dev.of_node,
                    "cardac,codec", 0);

    if (i2s_node) {
	   dai->cpu_dai_name = NULL;
	   dai->cpu_of_node = i2s_node;
       dai->platform_name = NULL;
	   dai->platform_of_node = i2s_node;
       dai->codec_name = NULL;
       dai->codec_of_node = codec_node;
    }

    cardac_clksel_gpio	= devm_gpiod_get(&pdev->dev, "clksel", GPIOD_OUT_LOW);
    cardac_mclk		= devm_clk_get (&pdev->dev, "mclk");
    cardac_plld		= devm_clk_get (&pdev->dev, "plld");
    if(IS_ERR(cardac_mclk)){ printk(KERN_INFO "cardac_mclk found");}
    else	   { printk(KERN_INFO "cardac_mclk not found");}
    if(*cardac_plld>=0){ printk(KERN_INFO "cardac_plld found");}
    else           { printk(KERN_INFO "cardac_plld not found");}

    ret =  clk_set_parent(cardac_mclk, cardac_plld);
    ret += clk_set_rate(cardac_mclk, 11289600);
    ret += clk_prepare_enable(cardac_plld);
    ret += clk_prepare_enable(cardac_mclk);
    if(ret<0) dev_err(&pdev->dev, "Clock Configuration Error");

    if(IS_ERR(cardac_clksel_gpio)){
        dev_err(&pdev->dev,"gpio not found");
        return cardac_clksel_gpio;
    }
	snd_soc_of_parse_card_name(&cardac_card, "cardac,model");
	ret = snd_soc_register_card(&cardac_card);
	if (ret != 0) {
		if (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev, "snd_soc_register_card() failed: %d\n",
					ret);
		return ret;
	}

	return ret;
}

static int cardac_remove(struct platform_device *pdev){
    return snd_soc_unregister_card(&cardac_card);
}

static const struct of_device_id cardac_of_match[] = {
	{ .compatible = "cardac,caramp", },
	{},
};
MODULE_DEVICE_TABLE(of, cardac_of_match);

static struct platform_driver cardac_driver = {
	.driver = {
		.name  = "snd-soc-cardac",
		.owner = THIS_MODULE,
		.of_match_table = cardac_of_match,
	},
	.probe  = cardac_probe,
	.remove = cardac_remove,
};

module_platform_driver(cardac_driver);

MODULE_AUTHOR("Karthik Karyamapudi <karthikkaryamapudi@gmail.com>");
MODULE_DESCRIPTION("ASoC Driver for CarDAC");
MODULE_LICENSE("GPL v2");
