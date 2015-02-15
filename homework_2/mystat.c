#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/unistd.h>

static void do_mem_stat(struct seq_file *i) {
  struct sysinfo  si;

  si_meminfo(&si);
  seq_printf(i, "RAM\n");
  seq_printf(i, "\ttotal\t%lu\n", si.totalram * si.mem_unit / 1024);
  seq_printf(i, "\tfree\t%lu\n", si.freeram * si.mem_unit / 1024);
  seq_printf(i, "\tshared\t%lu\n", si.sharedram * si.mem_unit / 1024);

}

static int  do_stat(struct seq_file *i, void *data) {
  do_mem_stat(i);
  return 0;
}

static int  open_callback(struct inode *ind, struct file *file) {
  return single_open(file, do_stat, NULL);
}

static const struct file_operations	proc_stat_operations = {
  .open = open_callback,
  .read = seq_read,
  .llseek = seq_lseek,
  .release = single_release
};

static int __init mystat_init(void) {
  proc_create("mystat", 0, NULL, &proc_stat_operations);
  printk(KERN_INFO "mystat module started\n");
  return 0;
}

static void __exit mystat_exit(void) {
  remove_proc_entry("mystat", NULL);
}

module_init(mystat_init);
module_exit(mystat_exit);
