
//program
#include <sys/shm.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/sem.h>
#include <time.h>
#include <stdio.h>
#define n 50


#define SIZEOFSHMSEG 200
#define APP_SHMAPPID 110022



//zmienne
struct shmid_ds buffer;

int shmid,size,flag;

unsigned *shmed;

char input;

key_t keySHM;





void Piszdane(int liczba){
			int object = 0;

			srand(time(NULL));


		 	shmed = (unsigned*) shmat(shmid, NULL, 0);


			for (object = 0; object < liczba; object++)
				{
					int tymczasowy = 0;
					do {
					tymczasowy = rand();
					} while ( (tymczasowy % 7) != 0);
					*(shmed+object) = tymczasowy;

					int number = *(shmed+object);


					printf("przechowywany numer to : %d \n",number);
				}

	}

unsigned char state[SIZEOFSHMSEG];
unsigned char lstate[SIZEOFSHMSEG];


	int shmini()
	{
		shmid = shmget(keySHM, size, IPC_CREAT | 0x1B6);
		if (shmid < 0)
		{
			printf("get error");
			perror("get");
			return 0;
		}
		else{
			printf("shmget success");
		}

		printf(" segment [%u][0x%x]\n\t",shmid, keySHM);
		return 1;
	}

	void shmdeini()
	{
           	 shmdt((void*)shmed);

	}




	void menu()
	{

 		keySHM = ftok("/root/dev/tmp", APP_SHMAPPID );
		flag = IPC_CREAT | 0x1B6;

		size = n*sizeof(unsigned);
		shmini();
	}

	void Drukuj(){
			int totalObj = n;
			int objInc = 0;
		 	shmed = (unsigned*) shmat(shmid, NULL, 0);

				for (objInc = 0; objInc < totalObj; objInc++)
				{
					int num = *(shmed+objInc);
					if ( (num % 7) == 0 )
						printf("%d \n",num);
				}

	}



	int main()
	{

	menu();

	while(input!= 'q')
	{
		printf("Co robimy  : p-pisz, c-czytaj, u-usun, q = quit \n");
//czytaj co robimy


		scanf("%c", &input);
		switch(input)
		{
			case 'p':
				Piszdane(n);
				break;

			case 'c':
				Drukuj();
				break;

			case 'u' :
				(void)shmctl(shmid, IPC_RMID, &buffer);
				break;

		}
	}


	//wypisanie wyniku

	shmdeini();

	return 0;

	}
