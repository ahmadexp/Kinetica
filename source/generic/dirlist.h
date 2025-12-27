#include <dirent.h>
#include <sys/stat.h>

const int maxdirentrys = 500;
class direntry{
	public:
		char filename[256];
		bool folder;
		int extrainfoint;
		direntry(const char* filename2){ snprintf(filename, sizeof(filename), "%s", filename2); folder=0; extrainfoint=0; }
};
static direntry *direntrys[maxdirentrys];
static int n_direntrys = 0;

void deletedirentry(int number){
	delete direntrys[number];
	direntrys[number]=NULL;
	if(number<n_direntrys-1)for(int a=number;a<n_direntrys;a++)direntrys[a]=direntrys[a+1];
	direntrys[n_direntrys-1]=NULL;
	n_direntrys=n_direntrys-1;
}

void dirlist(const char* directory){
	while(n_direntrys)deletedirentry(0);
	DIR *d = opendir(directory);
	if(!d) return;
	struct dirent *ent;
	while((ent = readdir(d))){
		if(n_direntrys>=maxdirentrys) break;
		direntrys[n_direntrys] = new direntry(ent->d_name);
		// detect folder
		if(ent->d_type==DT_DIR) direntrys[n_direntrys]->folder=1;
		else {
			// fallback: stat
			char pathbuf[PATH_MAX];
			snprintf(pathbuf, sizeof(pathbuf), "%s/%s", directory, ent->d_name);
			struct stat st;
			if(stat(pathbuf, &st)==0) if(S_ISDIR(st.st_mode)) direntrys[n_direntrys]->folder=1;
		}
		n_direntrys++;
	}
	closedir(d);
}
