/* Very rudimentary 9P fileserver */

#include <u.h>
#include <libc.h>
#include <mp.h>
#include <fcall.h>
#include <thread.h>
#include <9p.h>
#include <stdio.h>

Tree *glendatree;
typedef enum {QCTL} qpath;

/* glendasayfs only supports one operation.
 * 0222 /ctl
 *    	say <n>
 * 
 * e.g.
 * echo hello world > /n/glendasay/ctl
 * (glenda says hello world)
 * fortune > /n/glendasay/ctl
 * (glenda says whatever fortune returned)
 */

char*
ctlparse(char *line,  int len)
{
    char text[80];
    /* line is not null terminated */
    if (sscanf(line, "%[^\t\n]", text) == 1) {
	fprint(1,"        __\n");
	fprint(1,"       (  \\\n");
	fprint(1," __    \\   \\\n");
	fprint(1,"(  *-_ \\ .-`----._\n");
	fprint(1," `-_  *v*        *-\n");
	fprint(1,"    *Y*            *.     <");
	fprint(1,text);
	fprint(1,">\n");
	fprint(1,"     |               |   /\n");
	fprint(1,"     |       o    o  |  /\n");
	fprint(1,"     |         .<>.  |\n");
	fprint(1,"      \\        *Ll* |\n");
	fprint(1,"       |            .`\n");
	fprint(1,"       |            |\n");
	fprint(1,"       (            /\n");
	fprint(1,"      ('\          . \\ \n");
	fprint(1,"      \``--^--.__,\_)-'\n");
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


void usage(void)
{
    fprint(2,"usage: glendasayfs [-D] [-m mntpt]\n");
    exits("usage");
}

Srv fs = {
    //.open = fsopen,
    //.read = fsread,
    .write= fswrite
};

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
