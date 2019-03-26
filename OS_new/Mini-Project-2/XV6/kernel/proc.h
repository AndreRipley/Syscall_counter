#ifndef _PROC_H_
#define _PROC_H_
#define SEG_KCODE 1  
#define SEG_KDATA 2  
#define SEG_KCPU  3  
#define SEG_UCODE 4  
#define SEG_UDATA 5  
#define SEG_TSS   6  
#define NSEGS     7
#include "pstat.h"
#include "spinlock.h"

struct cpu {
	uchar id;                    
	struct context *scheduler;   
	struct taskstate ts;         
	struct segdesc gdt[NSEGS];   
	volatile uint booted;        
	int ncli;                    
	int intena;                  

	struct cpu *cpu;
	struct proc *proc;           
};

extern struct cpu cpus[NCPU];
extern int ncpu;

extern struct cpu *cpu asm("%gs:0");       
extern struct proc *proc asm("%gs:4");     

struct context {
	uint edi;
	uint esi;
	uint ebx;
	uint ebp;
	uint eip;
};

struct proc {
	uint sz;                     
	pde_t* pgdir;                
	char *kstack;                
	enum procstate state;        
	volatile int pid;            
	struct proc *parent;         
	struct trapframe *tf;        
	struct context *context;     
	void *chan;                  
	int killed;                  
	struct file *ofile[NOFILE];  
	struct inode *cwd;           
	char name[16];               

	_Bool inuse;
	int ticks;
	int tickets;

};

struct ptable_type {
	struct spinlock lock;
	struct proc proc[NPROC];
};
extern struct ptable_type ptable;


void setproctickets(struct proc* pp, int n);

#endif // _PROC_H_
