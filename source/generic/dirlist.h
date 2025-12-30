const int maxdirentrys = 500;
class direntry{
	public:
		char filename[256];
		bool folder;
		int extrainfoint;
		direntry(char* filename2);};
direntry::direntry(char* filename2){
    #ifdef _WIN32
	  sprintf_s(filename,"%s",filename2);
    #else
      snprintf(filename, sizeof(filename), "%s", filename2);
    #endif
	folder=0;
	extrainfoint=0;}
direntry *direntrys[maxdirentrys];
int n_direntrys = 0;

void deletedirentry(int number){
	delete direntrys[number];
	direntrys[number]=NULL;
	if(number<n_direntrys-1)for(int a=number;a<n_direntrys;a++)direntrys[a]=direntrys[a+1];
	direntrys[n_direntrys-1]=NULL;
	n_direntrys=n_direntrys-1;
}

#ifdef _WIN32
#include <windows.h>
void dirlist(char* directory){
	while(n_direntrys)deletedirentry(0);
	char filename[MAX_PATH];
	WIN32_FIND_DATAA findFileData;
	HANDLE hFind = FindFirstFileA(directory,&findFileData);
	if(hFind != INVALID_HANDLE_VALUE){
		bool endoflist=0;
		while(endoflist==0){
			sprintf_s(filename,"%s",findFileData.cFileName);
			direntrys[n_direntrys] = new direntry((char*)filename);
			if(findFileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)direntrys[n_direntrys]->folder=1;
			n_direntrys++;
			if(FindNextFileA(hFind,&findFileData)==0)endoflist=1;
		}
	}
}
#else
#include <dirent.h>
#include <sys/types.h>
#include <string>
#include <cstring>
#include <stdio.h>

void dirlist(char* directory){
	while(n_direntrys)deletedirentry(0);
	
    std::string path = directory;
    size_t wc = path.find('*');
    if(wc != std::string::npos) path = path.substr(0, wc);
    
    // opendir
    DIR* dir = opendir(path.c_str());
    if(dir){
        struct dirent* ent;
        while((ent = readdir(dir)) != NULL){
            if(strcmp(ent->d_name, ".")==0 || strcmp(ent->d_name, "..")==0) continue;
            
            direntrys[n_direntrys] = new direntry(ent->d_name);
            if(ent->d_type == DT_DIR) direntrys[n_direntrys]->folder=1;
            
            n_direntrys++;
            if(n_direntrys >= maxdirentrys) break;
        }
        closedir(dir);
    }
}
#endif
