/*
 * System call numbers.
 *
 * DO NOT EDIT-- this file is automatically @generated.
 */

				/* 0 is unimplemented linux_io_setup */
				/* 1 is unimplemented linux_io_destroy */
				/* 2 is unimplemented linux_io_submit */
				/* 3 is unimplemented linux_io_cancel */
				/* 4 is unimplemented linux_io_getevents */
#define	LINUX_SYS_linux_setxattr	5
#define	LINUX_SYS_linux_lsetxattr	6
#define	LINUX_SYS_linux_fsetxattr	7
#define	LINUX_SYS_linux_getxattr	8
#define	LINUX_SYS_linux_lgetxattr	9
#define	LINUX_SYS_linux_fgetxattr	10
#define	LINUX_SYS_linux_listxattr	11
#define	LINUX_SYS_linux_llistxattr	12
#define	LINUX_SYS_linux_flistxattr	13
#define	LINUX_SYS_linux_removexattr	14
#define	LINUX_SYS_linux_lremovexattr	15
#define	LINUX_SYS_linux_fremovexattr	16
#define	LINUX_SYS_linux_getcwd	17
#define	LINUX_SYS_linux_lookup_dcookie	18
#define	LINUX_SYS_linux_eventfd2	19
#define	LINUX_SYS_linux_epoll_create1	20
#define	LINUX_SYS_linux_epoll_ctl	21
#define	LINUX_SYS_linux_epoll_pwait	22
#define	LINUX_SYS_dup	23
#define	LINUX_SYS_linux_dup3	24
#define	LINUX_SYS_linux_fcntl	25
#define	LINUX_SYS_linux_inotify_init1	26
#define	LINUX_SYS_linux_inotify_add_watch	27
#define	LINUX_SYS_linux_inotify_rm_watch	28
#define	LINUX_SYS_linux_ioctl	29
#define	LINUX_SYS_linux_ioprio_set	30
#define	LINUX_SYS_linux_ioprio_get	31
#define	LINUX_SYS_flock	32
#define	LINUX_SYS_linux_mknodat	33
#define	LINUX_SYS_linux_mkdirat	34
#define	LINUX_SYS_linux_unlinkat	35
#define	LINUX_SYS_linux_symlinkat	36
#define	LINUX_SYS_linux_linkat	37
#define	LINUX_SYS_linux_renameat	38
				/* 39 is unimplemented linux_umount2 */
#define	LINUX_SYS_linux_mount	40
#define	LINUX_SYS_linux_pivot_root	41
				/* 42 is unimplemented nfsservctl */
#define	LINUX_SYS_linux_statfs	43
#define	LINUX_SYS_linux_fstatfs	44
#define	LINUX_SYS_linux_truncate	45
#define	LINUX_SYS_linux_ftruncate	46
#define	LINUX_SYS_linux_fallocate	47
#define	LINUX_SYS_linux_faccessat	48
#define	LINUX_SYS_linux_chdir	49
#define	LINUX_SYS_fchdir	50
#define	LINUX_SYS_chroot	51
#define	LINUX_SYS_fchmod	52
#define	LINUX_SYS_linux_fchmodat	53
#define	LINUX_SYS_linux_fchownat	54
#define	LINUX_SYS_fchown	55
#define	LINUX_SYS_linux_openat	56
#define	LINUX_SYS_close	57
#define	LINUX_SYS_linux_vhangup	58
#define	LINUX_SYS_linux_pipe2	59
				/* 60 is unimplemented linux_quotactl */
#define	LINUX_SYS_linux_getdents64	61
#define	LINUX_SYS_linux_lseek	62
#define	LINUX_SYS_read	63
#define	LINUX_SYS_linux_write	64
#define	LINUX_SYS_readv	65
#define	LINUX_SYS_linux_writev	66
#define	LINUX_SYS_linux_pread	67
#define	LINUX_SYS_linux_pwrite	68
#define	LINUX_SYS_linux_preadv	69
#define	LINUX_SYS_linux_pwritev	70
#define	LINUX_SYS_linux_sendfile	71
#define	LINUX_SYS_linux_pselect6	72
#define	LINUX_SYS_linux_ppoll	73
#define	LINUX_SYS_linux_signalfd4	74
#define	LINUX_SYS_linux_vmsplice	75
#define	LINUX_SYS_linux_splice	76
#define	LINUX_SYS_linux_tee	77
#define	LINUX_SYS_linux_readlinkat	78
#define	LINUX_SYS_linux_newfstatat	79
#define	LINUX_SYS_linux_newfstat	80
				/* 81 is unimplemented linux_sync */
#define	LINUX_SYS_fsync	82
#define	LINUX_SYS_linux_fdatasync	83
#define	LINUX_SYS_linux_sync_file_range	84
#define	LINUX_SYS_linux_timerfd_create	85
#define	LINUX_SYS_linux_timerfd_settime	86
#define	LINUX_SYS_linux_timerfd_gettime	87
#define	LINUX_SYS_linux_utimensat	88
#define	LINUX_SYS_acct	89
#define	LINUX_SYS_linux_capget	90
#define	LINUX_SYS_linux_capset	91
#define	LINUX_SYS_linux_personality	92
#define	LINUX_SYS_linux_exit	93
#define	LINUX_SYS_linux_exit_group	94
#define	LINUX_SYS_linux_waitid	95
#define	LINUX_SYS_linux_set_tid_address	96
#define	LINUX_SYS_linux_unshare	97
#define	LINUX_SYS_linux_sys_futex	98
#define	LINUX_SYS_linux_set_robust_list	99
#define	LINUX_SYS_linux_get_robust_list	100
#define	LINUX_SYS_linux_nanosleep	101
#define	LINUX_SYS_linux_getitimer	102
#define	LINUX_SYS_linux_setitimer	103
#define	LINUX_SYS_linux_kexec_load	104
#define	LINUX_SYS_linux_init_module	105
#define	LINUX_SYS_linux_delete_module	106
#define	LINUX_SYS_linux_timer_create	107
#define	LINUX_SYS_linux_timer_gettime	108
#define	LINUX_SYS_linux_timer_getoverrun	109
#define	LINUX_SYS_linux_timer_settime	110
#define	LINUX_SYS_linux_timer_delete	111
#define	LINUX_SYS_linux_clock_settime	112
#define	LINUX_SYS_linux_clock_gettime	113
#define	LINUX_SYS_linux_clock_getres	114
#define	LINUX_SYS_linux_clock_nanosleep	115
#define	LINUX_SYS_linux_syslog	116
#define	LINUX_SYS_linux_ptrace	117
#define	LINUX_SYS_linux_sched_setparam	118
#define	LINUX_SYS_linux_sched_setscheduler	119
#define	LINUX_SYS_linux_sched_getscheduler	120
#define	LINUX_SYS_linux_sched_getparam	121
#define	LINUX_SYS_linux_sched_setaffinity	122
#define	LINUX_SYS_linux_sched_getaffinity	123
#define	LINUX_SYS_sched_yield	124
#define	LINUX_SYS_linux_sched_get_priority_max	125
#define	LINUX_SYS_linux_sched_get_priority_min	126
#define	LINUX_SYS_linux_sched_rr_get_interval	127
				/* 128 is unimplemented restart_syscall */
#define	LINUX_SYS_linux_kill	129
#define	LINUX_SYS_linux_tkill	130
#define	LINUX_SYS_linux_tgkill	131
#define	LINUX_SYS_linux_sigaltstack	132
#define	LINUX_SYS_linux_rt_sigsuspend	133
#define	LINUX_SYS_linux_rt_sigaction	134
#define	LINUX_SYS_linux_rt_sigprocmask	135
#define	LINUX_SYS_linux_rt_sigpending	136
#define	LINUX_SYS_linux_rt_sigtimedwait	137
#define	LINUX_SYS_linux_rt_sigqueueinfo	138
#define	LINUX_SYS_linux_rt_sigreturn	139
#define	LINUX_SYS_setpriority	140
#define	LINUX_SYS_linux_getpriority	141
#define	LINUX_SYS_linux_reboot	142
#define	LINUX_SYS_setregid	143
#define	LINUX_SYS_setgid	144
#define	LINUX_SYS_setreuid	145
#define	LINUX_SYS_setuid	146
#define	LINUX_SYS_setresuid	147
#define	LINUX_SYS_getresuid	148
#define	LINUX_SYS_setresgid	149
#define	LINUX_SYS_getresgid	150
#define	LINUX_SYS_linux_setfsuid	151
#define	LINUX_SYS_linux_setfsgid	152
#define	LINUX_SYS_linux_times	153
#define	LINUX_SYS_setpgid	154
#define	LINUX_SYS_getpgid	155
#define	LINUX_SYS_linux_getsid	156
#define	LINUX_SYS_setsid	157
#define	LINUX_SYS_linux_getgroups	158
#define	LINUX_SYS_linux_setgroups	159
#define	LINUX_SYS_linux_newuname	160
#define	LINUX_SYS_linux_sethostname	161
#define	LINUX_SYS_linux_setdomainname	162
#define	LINUX_SYS_linux_getrlimit	163
#define	LINUX_SYS_linux_setrlimit	164
#define	LINUX_SYS_getrusage	165
#define	LINUX_SYS_umask	166
#define	LINUX_SYS_linux_prctl	167
#define	LINUX_SYS_linux_getcpu	168
#define	LINUX_SYS_gettimeofday	169
#define	LINUX_SYS_settimeofday	170
#define	LINUX_SYS_linux_adjtimex	171
#define	LINUX_SYS_linux_getpid	172
#define	LINUX_SYS_linux_getppid	173
#define	LINUX_SYS_linux_getuid	174
#define	LINUX_SYS_geteuid	175
#define	LINUX_SYS_linux_getgid	176
#define	LINUX_SYS_getegid	177
#define	LINUX_SYS_linux_gettid	178
#define	LINUX_SYS_linux_sysinfo	179
#define	LINUX_SYS_linux_mq_open	180
#define	LINUX_SYS_linux_mq_unlink	181
#define	LINUX_SYS_linux_mq_timedsend	182
#define	LINUX_SYS_linux_mq_timedreceive	183
#define	LINUX_SYS_linux_mq_notify	184
#define	LINUX_SYS_linux_mq_getsetattr	185
#define	LINUX_SYS_linux_msgget	186
#define	LINUX_SYS_linux_msgctl	187
#define	LINUX_SYS_linux_msgrcv	188
#define	LINUX_SYS_linux_msgsnd	189
#define	LINUX_SYS_linux_semget	190
#define	LINUX_SYS_linux_semctl	191
#define	LINUX_SYS_linux_semtimedop	192
#define	LINUX_SYS_semop	193
#define	LINUX_SYS_linux_shmget	194
#define	LINUX_SYS_linux_shmctl	195
#define	LINUX_SYS_linux_shmat	196
#define	LINUX_SYS_linux_shmdt	197
#define	LINUX_SYS_linux_socket	198
#define	LINUX_SYS_linux_socketpair	199
#define	LINUX_SYS_linux_bind	200
#define	LINUX_SYS_linux_listen	201
#define	LINUX_SYS_linux_accept	202
#define	LINUX_SYS_linux_connect	203
#define	LINUX_SYS_linux_getsockname	204
#define	LINUX_SYS_linux_getpeername	205
#define	LINUX_SYS_linux_sendto	206
#define	LINUX_SYS_linux_recvfrom	207
#define	LINUX_SYS_linux_setsockopt	208
#define	LINUX_SYS_linux_getsockopt	209
#define	LINUX_SYS_linux_shutdown	210
#define	LINUX_SYS_linux_sendmsg	211
#define	LINUX_SYS_linux_recvmsg	212
				/* 213 is unimplemented linux_readahead */
#define	LINUX_SYS_linux_brk	214
#define	LINUX_SYS_munmap	215
#define	LINUX_SYS_linux_mremap	216
#define	LINUX_SYS_linux_add_key	217
#define	LINUX_SYS_linux_request_key	218
#define	LINUX_SYS_linux_keyctl	219
#define	LINUX_SYS_linux_clone	220
#define	LINUX_SYS_linux_execve	221
#define	LINUX_SYS_linux_mmap2	222
#define	LINUX_SYS_linux_fadvise64	223
#define	LINUX_SYS_swapon	224
#define	LINUX_SYS_linux_swapoff	225
#define	LINUX_SYS_linux_mprotect	226
#define	LINUX_SYS_linux_msync	227
#define	LINUX_SYS_mlock	228
#define	LINUX_SYS_munlock	229
#define	LINUX_SYS_mlockall	230
#define	LINUX_SYS_munlockall	231
#define	LINUX_SYS_linux_mincore	232
#define	LINUX_SYS_linux_madvise	233
#define	LINUX_SYS_linux_remap_file_pages	234
#define	LINUX_SYS_linux_mbind	235
#define	LINUX_SYS_linux_get_mempolicy	236
#define	LINUX_SYS_linux_set_mempolicy	237
#define	LINUX_SYS_linux_migrate_pages	238
#define	LINUX_SYS_linux_move_pages	239
#define	LINUX_SYS_linux_rt_tgsigqueueinfo	240
#define	LINUX_SYS_linux_perf_event_open	241
#define	LINUX_SYS_linux_accept4	242
#define	LINUX_SYS_linux_recvmmsg	243
				/* 244 is unimplemented unimpl_md_syscall */
				/* 245 is unimplemented unimpl_md_syscall */
				/* 246 is unimplemented unimpl_md_syscall */
				/* 247 is unimplemented unimpl_md_syscall */
				/* 248 is unimplemented unimpl_md_syscall */
				/* 249 is unimplemented unimpl_md_syscall */
				/* 250 is unimplemented unimpl_md_syscall */
				/* 251 is unimplemented unimpl_md_syscall */
				/* 252 is unimplemented unimpl_md_syscall */
				/* 253 is unimplemented unimpl_md_syscall */
				/* 254 is unimplemented unimpl_md_syscall */
				/* 255 is unimplemented unimpl_md_syscall */
				/* 256 is unimplemented unimpl_md_syscall */
				/* 257 is unimplemented unimpl_md_syscall */
				/* 258 is unimplemented unimpl_md_syscall */
				/* 259 is unimplemented unimpl_md_syscall */
#define	LINUX_SYS_linux_wait4	260
#define	LINUX_SYS_linux_prlimit64	261
#define	LINUX_SYS_linux_fanotify_init	262
#define	LINUX_SYS_linux_fanotify_mark	263
#define	LINUX_SYS_linux_name_to_handle_at	264
#define	LINUX_SYS_linux_open_by_handle_at	265
#define	LINUX_SYS_linux_clock_adjtime	266
#define	LINUX_SYS_linux_syncfs	267
#define	LINUX_SYS_linux_setns	268
#define	LINUX_SYS_linux_sendmmsg	269
#define	LINUX_SYS_linux_process_vm_readv	270
#define	LINUX_SYS_linux_process_vm_writev	271
#define	LINUX_SYS_linux_kcmp	272
#define	LINUX_SYS_linux_finit_module	273
#define	LINUX_SYS_linux_sched_setattr	274
#define	LINUX_SYS_linux_sched_getattr	275
#define	LINUX_SYS_linux_renameat2	276
#define	LINUX_SYS_linux_seccomp	277
#define	LINUX_SYS_linux_getrandom	278
#define	LINUX_SYS_linux_memfd_create	279
#define	LINUX_SYS_linux_bpf	280
#define	LINUX_SYS_linux_execveat	281
#define	LINUX_SYS_linux_userfaultfd	282
#define	LINUX_SYS_linux_membarrier	283
#define	LINUX_SYS_linux_mlock2	284
#define	LINUX_SYS_linux_copy_file_range	285
#define	LINUX_SYS_linux_preadv2	286
#define	LINUX_SYS_linux_pwritev2	287
#define	LINUX_SYS_linux_pkey_mprotect	288
#define	LINUX_SYS_linux_pkey_alloc	289
#define	LINUX_SYS_linux_pkey_free	290
#define	LINUX_SYS_linux_statx	291
#define	LINUX_SYS_linux_io_pgetevents	292
#define	LINUX_SYS_linux_rseq	293
#define	LINUX_SYS_linux_kexec_file_load	294
				/* 295 is unimplemented unimpl_md_syscall */
				/* 296 is unimplemented unimpl_md_syscall */
				/* 297 is unimplemented unimpl_md_syscall */
				/* 298 is unimplemented unimpl_md_syscall */
				/* 299 is unimplemented unimpl_md_syscall */
				/* 300 is unimplemented unimpl_md_syscall */
				/* 301 is unimplemented unimpl_md_syscall */
				/* 302 is unimplemented unimpl_md_syscall */
				/* 303 is unimplemented unimpl_md_syscall */
				/* 304 is unimplemented unimpl_md_syscall */
				/* 305 is unimplemented unimpl_md_syscall */
				/* 306 is unimplemented unimpl_md_syscall */
				/* 307 is unimplemented unimpl_md_syscall */
				/* 308 is unimplemented unimpl_md_syscall */
				/* 309 is unimplemented unimpl_md_syscall */
				/* 310 is unimplemented unimpl_md_syscall */
				/* 311 is unimplemented unimpl_md_syscall */
				/* 312 is unimplemented unimpl_md_syscall */
				/* 313 is unimplemented unimpl_md_syscall */
				/* 314 is unimplemented unimpl_md_syscall */
				/* 315 is unimplemented unimpl_md_syscall */
				/* 316 is unimplemented unimpl_md_syscall */
				/* 317 is unimplemented unimpl_md_syscall */
				/* 318 is unimplemented unimpl_md_syscall */
				/* 319 is unimplemented unimpl_md_syscall */
				/* 320 is unimplemented unimpl_md_syscall */
				/* 321 is unimplemented unimpl_md_syscall */
				/* 322 is unimplemented unimpl_md_syscall */
				/* 323 is unimplemented unimpl_md_syscall */
				/* 324 is unimplemented unimpl_md_syscall */
				/* 325 is unimplemented unimpl_md_syscall */
				/* 326 is unimplemented unimpl_md_syscall */
				/* 327 is unimplemented unimpl_md_syscall */
				/* 328 is unimplemented unimpl_md_syscall */
				/* 329 is unimplemented unimpl_md_syscall */
				/* 330 is unimplemented unimpl_md_syscall */
				/* 331 is unimplemented unimpl_md_syscall */
				/* 332 is unimplemented unimpl_md_syscall */
				/* 333 is unimplemented unimpl_md_syscall */
				/* 334 is unimplemented unimpl_md_syscall */
				/* 335 is unimplemented unimpl_md_syscall */
				/* 336 is unimplemented unimpl_md_syscall */
				/* 337 is unimplemented unimpl_md_syscall */
				/* 338 is unimplemented unimpl_md_syscall */
				/* 339 is unimplemented unimpl_md_syscall */
				/* 340 is unimplemented unimpl_md_syscall */
				/* 341 is unimplemented unimpl_md_syscall */
				/* 342 is unimplemented unimpl_md_syscall */
				/* 343 is unimplemented unimpl_md_syscall */
				/* 344 is unimplemented unimpl_md_syscall */
				/* 345 is unimplemented unimpl_md_syscall */
				/* 346 is unimplemented unimpl_md_syscall */
				/* 347 is unimplemented unimpl_md_syscall */
				/* 348 is unimplemented unimpl_md_syscall */
				/* 349 is unimplemented unimpl_md_syscall */
				/* 350 is unimplemented unimpl_md_syscall */
				/* 351 is unimplemented unimpl_md_syscall */
				/* 352 is unimplemented unimpl_md_syscall */
				/* 353 is unimplemented unimpl_md_syscall */
				/* 354 is unimplemented unimpl_md_syscall */
				/* 355 is unimplemented unimpl_md_syscall */
				/* 356 is unimplemented unimpl_md_syscall */
				/* 357 is unimplemented unimpl_md_syscall */
				/* 358 is unimplemented unimpl_md_syscall */
				/* 359 is unimplemented unimpl_md_syscall */
				/* 360 is unimplemented unimpl_md_syscall */
				/* 361 is unimplemented unimpl_md_syscall */
				/* 362 is unimplemented unimpl_md_syscall */
				/* 363 is unimplemented unimpl_md_syscall */
				/* 364 is unimplemented unimpl_md_syscall */
				/* 365 is unimplemented unimpl_md_syscall */
				/* 366 is unimplemented unimpl_md_syscall */
				/* 367 is unimplemented unimpl_md_syscall */
				/* 368 is unimplemented unimpl_md_syscall */
				/* 369 is unimplemented unimpl_md_syscall */
				/* 370 is unimplemented unimpl_md_syscall */
				/* 371 is unimplemented unimpl_md_syscall */
				/* 372 is unimplemented unimpl_md_syscall */
				/* 373 is unimplemented unimpl_md_syscall */
				/* 374 is unimplemented unimpl_md_syscall */
				/* 375 is unimplemented unimpl_md_syscall */
				/* 376 is unimplemented unimpl_md_syscall */
				/* 377 is unimplemented unimpl_md_syscall */
				/* 378 is unimplemented unimpl_md_syscall */
				/* 379 is unimplemented unimpl_md_syscall */
				/* 380 is unimplemented unimpl_md_syscall */
				/* 381 is unimplemented unimpl_md_syscall */
				/* 382 is unimplemented unimpl_md_syscall */
				/* 383 is unimplemented unimpl_md_syscall */
				/* 384 is unimplemented unimpl_md_syscall */
				/* 385 is unimplemented unimpl_md_syscall */
				/* 386 is unimplemented unimpl_md_syscall */
				/* 387 is unimplemented unimpl_md_syscall */
				/* 388 is unimplemented unimpl_md_syscall */
				/* 389 is unimplemented unimpl_md_syscall */
				/* 390 is unimplemented unimpl_md_syscall */
				/* 391 is unimplemented unimpl_md_syscall */
				/* 392 is unimplemented unimpl_md_syscall */
				/* 393 is unimplemented unimpl_md_syscall */
				/* 394 is unimplemented unimpl_md_syscall */
				/* 395 is unimplemented unimpl_md_syscall */
				/* 396 is unimplemented unimpl_md_syscall */
				/* 397 is unimplemented unimpl_md_syscall */
				/* 398 is unimplemented unimpl_md_syscall */
				/* 399 is unimplemented unimpl_md_syscall */
				/* 400 is unimplemented unimpl_md_syscall */
				/* 401 is unimplemented unimpl_md_syscall */
				/* 402 is unimplemented unimpl_md_syscall */
				/* 403 is unimplemented unimpl_md_syscall */
				/* 404 is unimplemented unimpl_md_syscall */
				/* 405 is unimplemented unimpl_md_syscall */
				/* 406 is unimplemented unimpl_md_syscall */
				/* 407 is unimplemented unimpl_md_syscall */
				/* 408 is unimplemented unimpl_md_syscall */
				/* 409 is unimplemented unimpl_md_syscall */
				/* 410 is unimplemented unimpl_md_syscall */
				/* 411 is unimplemented unimpl_md_syscall */
				/* 412 is unimplemented unimpl_md_syscall */
				/* 413 is unimplemented unimpl_md_syscall */
				/* 414 is unimplemented unimpl_md_syscall */
				/* 415 is unimplemented unimpl_md_syscall */
				/* 416 is unimplemented unimpl_md_syscall */
				/* 417 is unimplemented unimpl_md_syscall */
				/* 418 is unimplemented unimpl_md_syscall */
				/* 419 is unimplemented unimpl_md_syscall */
				/* 420 is unimplemented unimpl_md_syscall */
				/* 421 is unimplemented unimpl_md_syscall */
				/* 422 is unimplemented unimpl_md_syscall */
				/* 423 is unimplemented unimpl_md_syscall */
#define	LINUX_SYS_linux_pidfd_send_signal	424
#define	LINUX_SYS_linux_io_uring_setup	425
#define	LINUX_SYS_linux_io_uring_enter	426
#define	LINUX_SYS_linux_io_uring_register	427
#define	LINUX_SYS_linux_open_tree	428
#define	LINUX_SYS_linux_move_mount	429
#define	LINUX_SYS_linux_fsopen	430
#define	LINUX_SYS_linux_fsconfig	431
#define	LINUX_SYS_linux_fsmount	432
#define	LINUX_SYS_linux_fspick	433
#define	LINUX_SYS_linux_pidfd_open	434
#define	LINUX_SYS_linux_clone3	435
#define	LINUX_SYS_linux_close_range	436
#define	LINUX_SYS_linux_openat2	437
#define	LINUX_SYS_linux_pidfd_getfd	438
#define	LINUX_SYS_linux_faccessat2	439
#define	LINUX_SYS_linux_process_madvise	440
#define	LINUX_SYS_linux_epoll_pwait2	441
#define	LINUX_SYS_linux_mount_setattr	442
#define	LINUX_SYS_linux_quotactl_fd	443
#define	LINUX_SYS_linux_landlock_create_ruleset	444
#define	LINUX_SYS_linux_landlock_add_rule	445
#define	LINUX_SYS_linux_landlock_restrict_self	446
#define	LINUX_SYS_linux_memfd_secret	447
#define	LINUX_SYS_linux_process_mrelease	448
#define	LINUX_SYS_linux_futex_waitv	449
#define	LINUX_SYS_linux_set_mempolicy_home_node	450
#define	LINUX_SYS_linux_cachestat	451
#define	LINUX_SYS_linux_fchmodat2	452
#define	LINUX_SYS_MAXSYSCALL	453