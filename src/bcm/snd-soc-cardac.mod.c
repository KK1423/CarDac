#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xdb0d8ebc, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xb077e70a, __VMLINUX_SYMBOL_STR(clk_unprepare) },
	{ 0x815588a6, __VMLINUX_SYMBOL_STR(clk_enable) },
	{ 0x31d5608b, __VMLINUX_SYMBOL_STR(snd_soc_of_parse_card_name) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x3dd3f751, __VMLINUX_SYMBOL_STR(of_parse_phandle) },
	{ 0x4951ecaa, __VMLINUX_SYMBOL_STR(devm_gpiod_get) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x88dc7e6f, __VMLINUX_SYMBOL_STR(__platform_driver_register) },
	{ 0xb87cadfc, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xa785a330, __VMLINUX_SYMBOL_STR(snd_soc_unregister_card) },
	{ 0xc559ed61, __VMLINUX_SYMBOL_STR(snd_soc_dai_set_bclk_ratio) },
	{ 0x2396c7f0, __VMLINUX_SYMBOL_STR(clk_set_parent) },
	{ 0x7c9a7371, __VMLINUX_SYMBOL_STR(clk_prepare) },
	{ 0x8c211eeb, __VMLINUX_SYMBOL_STR(devm_clk_get) },
	{ 0x76d9b876, __VMLINUX_SYMBOL_STR(clk_set_rate) },
	{ 0x6c2ed63d, __VMLINUX_SYMBOL_STR(snd_soc_dai_set_fmt) },
	{ 0x397ca8aa, __VMLINUX_SYMBOL_STR(gpiod_set_value_cansleep) },
	{ 0xfc01da1c, __VMLINUX_SYMBOL_STR(platform_driver_unregister) },
	{ 0x24e70d12, __VMLINUX_SYMBOL_STR(snd_soc_register_card) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=snd-soc-core";

MODULE_ALIAS("of:N*T*Ccardac,caramp");
MODULE_ALIAS("of:N*T*Ccardac,carampC*");

MODULE_INFO(srcversion, "0028F31ADF89372EF02A731");
