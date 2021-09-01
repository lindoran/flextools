#include "directory.h"

void dir_get_filename(t_dir_entry *dir,char *str) {

    for(int i=0;i<8;i ++) {
        if (dir->filename[i]==0) break;
        *str++=dir->filename[i];
    }

    *str++='.';

    for(int i=0;i<3;i ++) {
        if (dir->ext[i]==0) break;
        *str++=dir->ext[i];
    }

    *str='\0';
}
