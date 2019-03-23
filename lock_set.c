//
// Created by zk on 19-3-22.
//
#include <stdio.h>
#include <fcntl.h>
#include <zconf.h>

extern int lock_set(int fd, short type)
{
    struct flock old_lock, lock;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_type = type;
    lock.l_pid = -1;

    fcntl(fd, F_GETLK, &lock);//测试文件是否能够上锁

    if(lock.l_type != F_UNLCK)//如果不能上锁
    {
        if(lock.l_type == F_RDLCK)//如果文件已经有读取锁
        {
            printf("Read lock already set by %d\n", lock.l_pid);
        } else if(lock.l_type == F_WRLCK)//如果文件已经有写入锁
        {
            printf("Write lock already set by %d\n", lock.l_pid);
        }

    }


    lock.l_type = type;

    if((fcntl(fd, F_SETLKW, &lock)) < 0)
    {
        printf("Lock failed:type = %d\n",lock.l_type);
    }

    switch (lock.l_type)
    {
        case F_RDLCK:
        {
            printf("Read lock set by %d\n", getpid());
        }
            break;
        case F_WRLCK:
        {
            printf("Write lock set by %d\n", getpid());
        }
            break;
        case F_UNLCK:
        {
            printf("Release lock by %d\n", getpid());
        }
            break;
    }
    return 0;
}