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
	{ 0xe56a9336, __VMLINUX_SYMBOL_STR(snd_pcm_format_width) },
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xd9ead207, __VMLINUX_SYMBOL_STR(i2c_del_driver) },
	{ 0x52eb2dc5, __VMLINUX_SYMBOL_STR(regmap_update_bits_base) },
	{ 0x6b06fdce, __VMLINUX_SYMBOL_STR(delayed_work_timer_fn) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x8fdf772a, __VMLINUX_SYMBOL_STR(init_timer_key) },
	{ 0xa0744ea9, __VMLINUX_SYMBOL_STR(cancel_delayed_work_sync) },
	{ 0xcb5daba2, __VMLINUX_SYMBOL_STR(snd_soc_put_volsw) },
	{ 0xe1250b50, __VMLINUX_SYMBOL_STR(regmap_read) },
	{ 0x66da0eca, __VMLINUX_SYMBOL_STR(snd_soc_get_volsw) },
	{ 0x40cd8942, __VMLINUX_SYMBOL_STR(devm_regulator_bulk_get) },
	{ 0x7dd91565, __VMLINUX_SYMBOL_STR(regulator_bulk_enable) },
	{ 0xb87cadfc, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0xac92dc30, __VMLINUX_SYMBOL_STR(snd_soc_update_bits) },
	{ 0xea523ef2, __VMLINUX_SYMBOL_STR(dev_crit) },
	{ 0x94680ad3, __VMLINUX_SYMBOL_STR(snd_soc_info_volsw) },
	{ 0xf204b815, __VMLINUX_SYMBOL_STR(i2c_register_driver) },
	{ 0x7a5c74ff, __VMLINUX_SYMBOL_STR(regulator_bulk_disable) },
	{ 0x85d472aa, __VMLINUX_SYMBOL_STR(queue_delayed_work_on) },
	{ 0xff227eee, __VMLINUX_SYMBOL_STR(__devm_regmap_init_i2c) },
	{ 0xee9ce628, __VMLINUX_SYMBOL_STR(snd_soc_unregister_codec) },
	{ 0x314cad3d, __VMLINUX_SYMBOL_STR(regcache_mark_dirty) },
	{ 0x1b3b9517, __VMLINUX_SYMBOL_STR(dev_warn) },
	{ 0x103b85f7, __VMLINUX_SYMBOL_STR(snd_soc_register_codec) },
	{ 0x40c57909, __VMLINUX_SYMBOL_STR(devm_kmalloc) },
	{ 0xad83053c, __VMLINUX_SYMBOL_STR(regcache_sync) },
	{ 0x99b90480, __VMLINUX_SYMBOL_STR(regcache_cache_only) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=snd-pcm,snd-soc-core";

MODULE_ALIAS("i2c:tas6424");
MODULE_ALIAS("of:N*T*Cti,tas6424");
MODULE_ALIAS("of:N*T*Cti,tas6424C*");

MODULE_INFO(srcversion, "C25D36C02BA1D6AB42D89A9");
