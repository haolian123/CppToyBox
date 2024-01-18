#include"mytree.h"


int main(int argc,char**argv){
    std::shared_ptr<FileTree>fileTree;
    if(argc<2){
        fileTree->tree("..");
    }else{
        fileTree->tree(std::string(argv[1]));
    }
}