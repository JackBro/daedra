#include <linux/init.h>
#include <linux/module.h>

static int __init cloakd_init(void)
{
	return 0;
}

static void __exit cloakd_exit(void)
{}


module_init(cloakd_init);
module_exit(cloakd_exit);
