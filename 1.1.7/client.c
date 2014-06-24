#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int
main(int argc, char **argv)
{
    int ret, reste = -1, fdr, fdw;
    int achat = 0, engagement = 0;
    char c;

    if(argc != 3)
    {
        printf("usage : %s fifo_write fifo_read\n", argv[0]);
        exit(1);
    }

    fdw = open(argv[1], O_WRONLY);
    if(fdw < 0)
    {
        perror("pb ouverture fifo ecriture");
        exit(1);
    }
    
    fdr = open (argv[2],O_RDONLY);
    if(fdr < 0)
    {
        perror("pb ouverture fifo lecture");
        exit(1);
    }

    printf("objectif : acheter la derniere place (reste = 0)\n\
        moitiee des places si reste plus de place\n\
        engagement perdu si reste negatif ou abandon\n");
    
    printf("regle du jeu : 'v' pour voir le reste,\n\
        'a' pour payer puis  acheter\n");
    
    while(reste!=0)
    {
        ret = read(0, &c, 1);
        
        if(ret < 0)
        {
            perror("pb lecture clavier");
            exit(1);
        }
        
        if (c == 'a')
        {
            engagement+=500;
            printf("paiement en cours, attendez!\n");
            usleep(5000000);
        }

        ret=write(fdw,&c,1);
        
        if(ret < 0)
        {
            perror("pb ecriture fifo ");
            exit(1);
        }
        
        ret=read(fdr, &reste, sizeof reste);
        
        if(ret < 0)
        {
            perror("pb lecture fifo");
            exit(1);
        }
        
        if (reste < 1 && c=='v')
        {
            achat = achat / 2;
            printf("fini! reste: %d achat : %d engagement: %d\n",
                reste, achat, engagement);
            
            break;
        }
        
        if(reste < 0 && c=='a')
        {
            achat=0;
            printf("you loose ! achat:%d engagement: %d\n",
                achat, engagement);

            break;
        }

        if (reste == 0 && c=='a')
        {
            achat++;
            printf("you win! reste: %d achat: %d engagement :%d \n", 
                reste, achat, engagement);

            break;
        }

        if (reste > 0 && c=='a')
        {
            achat++;
            printf("reste:%d achat : %d, engagement : %d\n",
                reste, achat, engagement);

            continue;
        }

        if (reste > 0 && c=='v')
        {
            printf("reste:  %d achat: %d engagement: %d\n",
                reste, achat,engagement);
        }
    } 
    
    pause();
    return 0;
}
