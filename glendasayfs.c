/* Very rudimentary 9P fileserver */

#include <u.h>
#include <libc.h>
#include <mp.h>
#include <fcall.h>
#include <thread.h>
#include <9p.h>

Tree *glendatree;
typedef enum {QCTL} qpath;

Srv fs = {
    //.open = fsopen,
    .read = fsread,
    .write= fswrite
};

/*
 * 0222 /ctl
 *      say <n>
 */

char*
ctlparse(char *line,  int len)
{
    /* line is not null terminated */
    if(strncmp(line, "say", 3) == 0){

 	fprint(1,"(\\(\\ \n");
 	fprint(1,"( . .)\n");
 	fprint(1," | ° ¡\n");
 	fprint(1," ¿   ;\n");
 	fprint(1,"c?.UJ\n");
    } 
    /* could potentially add more commands in a switch */
    return nil;
}


void
fswrite(Req *r) {
    switch(r->fid->qid.path) {
        case QCTL:
            ctlparse(r->ifcall.data, r->ifcall.count);
            break;
        default:
            break;
    }
    respond(r, nil);
}

void
fsread(Req *r) {
    return nil;
}

void usage(void)
{
    fprint(2,"usage: glendasayfs [-D] [-m mntpt]\n");
    exits("usage");
}

void
main(int argc,char *argv[])
{
    char *mntpt = "/n/glendasay";

    ARGBEGIN{
        case 'D':
            chatty9p++;
            break;
        case 'm':
            mntpt = EARGF(usage());
            break;

    }ARGEND;

    /* Create file tree and populate */
    fs.tree = glendatree = alloctree("none","none",DMDIR|0555,nil);
    closefile(createfile(glendatree->root,"ctl","none",0222,nil)); // write only
    postmountsrv(&fs,nil,mntpt,MAFTER);

    exits(nil);
}
