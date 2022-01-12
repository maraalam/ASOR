#include <sys/types.h>  //stat
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>      //error
#include <errno.h>
#include <string.h>

#include <time.h>       //ctime


int main(int argc, char *argv[]){

    if(argc < 2){
        fprintf(stderr,"[ERROR] Incorrect parameters\n");
        exit(1);
    }

    struct stat buf;

    if(stat(argv[1] , &buf) == -1){
        perror("stat");
        exit(1);
    }
    
    char *type = "";



    switch (buf.st_mode & S_IFMT) {
        case S_IFBLK:  type = "block device";         break;
        case S_IFCHR:  type = "character device";     break;
        case S_IFDIR:  type = "directory";            break;
        case S_IFIFO:  type = "FIFO/pipe";            break;
        case S_IFLNK:  type = "symlink";              break;
        case S_IFREG:  type = "regular file";         break;
        case S_IFSOCK: type = "socket";               break;
        default:       type = "unknown?";             break;
    }


    printf("File: '%s'        Type: %s\n",argv[1],type);

    printf("Size: %d         	Blocks: %lld         	IO Block: %d\n", 
        buf.st_size, (long) buf.st_blocks, buf.st_blksize);

    printf("Device: [%lx,%lx]            Inode:  %ld        Links: %d\n", 
        (long) major(buf.st_dev), (long) minor(buf.st_dev), (long) buf.st_ino, buf.st_nlink);

    printf("Uid: %d               Gid: %d\n", buf.st_uid, buf.st_gid);

    printf("Access: %s", ctime(&buf.st_atime));
    printf("Modify: %s", ctime(&buf.st_mtime));
    printf("Change: %s", ctime(&buf.st_ctime));



    return 0;
}
