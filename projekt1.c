#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


int main(int argc, char *argv[])
{
// Todo
int process = 10;

int parentpid =0;
//jezeli liczba procesow jest wieksza od 2000 zakoncz przekroczono tablice
if ( process >200 )
{
	printf("TPrzekroczono tablice procesów \n");
	exit(1);
}




// Jezeli liczba procesów jest wieksza od 0 to rób
else if ( process > 0 )
{
int procs[200];
//przypisz proces rodzica
parentpid = getpid();
//wyswietlk proces
printf("List of %d processes \n",process);

printf("Proces pierwszy : ID\t%d\n Rodzic :%d \n",(int) getpid(),getppid());
int proc = 0;
// Petla jezeli procesow jest mniej niz 200 to zapisz tn proces do tabeli
for ( proc = 0; proc<process; proc++)
{
	procs[proc]	=	fork();




	switch(procs[proc])
	{
	case 0:

		pause();

	case -1:

		exit(1);
	}

	printf("Proces potomny nr %d \t ma id %d , Rodzic :%d \t \n",proc,procs[proc],parentpid);
}



//rob dopuki liczba procesow jest wieksza od 0
while(process > 0)
{

//jezeli proces potomny ronwa sie procesowi podanemu zakoncz program

printf("Podaj kod procesu potomnego do usuniecia\n");

int makedelete = 0;
scanf("%d",&makedelete);


for ( process = 10; process<proc; proces)
{


	printf("Proces potomny nr %d \t ma id %d , Rodzic :%d \t \n",proc,procs[proc],parentpid);
}



printf("Aby zakonczyc zabij proces macierzysty\n");
if (makedelete == parentpid )
{
	printf("zabij proces  macierzysty  ");
	printf("Thanks for using this program  ");
	exit(1);
}

int id = 0;

// jezeli petla znajdzie podanyproces to go zabija
	for ( id = 0; id < process; id++)
	{
		if ( makedelete == procs[id] )
		{
			kill(makedelete,SIGKILL);
				printf("Usunieto process child:  %d \t \n",procs[id]);
		}
	}
 }
}
else
{
	printf("zbyt duza liczba procesow  \n");

	printf("Dziekujemy za korzystanie z programu zacznij jeszcze raz  \n");
	exit(1);
}
return 0;
}
