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
	{ 0xcec0b425, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xeae3dfd6, __VMLINUX_SYMBOL_STR(__const_udelay) },
	{ 0x779a18af, __VMLINUX_SYMBOL_STR(kstrtoll) },
	{ 0x687934e9, __VMLINUX_SYMBOL_STR(gpiod_set_raw_value) },
	{ 0xf816c866, __VMLINUX_SYMBOL_STR(gpio_to_desc) },
	{ 0xfe990052, __VMLINUX_SYMBOL_STR(gpio_free) },
	{ 0xc9e82ae0, __VMLINUX_SYMBOL_STR(class_unregister) },
	{ 0x20c92f69, __VMLINUX_SYMBOL_STR(cdev_del) },
	{ 0x403f9529, __VMLINUX_SYMBOL_STR(gpio_request_one) },
	{ 0x9d3e48b0, __VMLINUX_SYMBOL_STR(__class_register) },
	{ 0xbc0de96c, __VMLINUX_SYMBOL_STR(device_destroy) },
	{ 0x3c25b5d6, __VMLINUX_SYMBOL_STR(cdev_add) },
	{ 0x9a505f82, __VMLINUX_SYMBOL_STR(cdev_init) },
	{ 0xccc60a67, __VMLINUX_SYMBOL_STR(class_destroy) },
	{ 0x34df29ee, __VMLINUX_SYMBOL_STR(device_create) },
	{ 0x7485e15e, __VMLINUX_SYMBOL_STR(unregister_chrdev_region) },
	{ 0x3712dd7d, __VMLINUX_SYMBOL_STR(__class_create) },
	{ 0x29537c9e, __VMLINUX_SYMBOL_STR(alloc_chrdev_region) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "63AA7C6D24025296A15564B");
