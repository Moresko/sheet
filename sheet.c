#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

#define max_lenght 10240

//ulozi textovy subor 
int save(int velkost, char subor[])
{
   int znaky;
   while((znaky = getchar()) != EOF){
      subor[velkost] = znaky;
      velkost++;
  }  
   return velkost;
}

//funkcia nastavi retazec delim do textu
void edit_delimeter(char delim[],char ulozisko[])
{
  int i = 0;	
  while(ulozisko[i] != '\0')
  {
    if(strchr(delim,ulozisko[i]) != NULL)
    {
      ulozisko[i] = delim[0]; // zmeni vsetky delimetre na prvy v retazci
    }
    i++;     
  }	  
  return;  
}

//tato funkcia zabezpeci to ze dalsi znak po -d bude nastaveny ako separator v danom texte 
char delimeter(int argc, char *argv[], char ulozisko[])
{
  for(int i = 1; i < argc; i++)
  {
    if(strcmp(argv[1],"-d") == 0 && i + 1 < argc)
    {
      edit_delimeter(argv[i + 1], ulozisko);  
      return argv[i + 1][0];
    }  
  } 
 return ' '; 
}	

/*funckia acol v prvom kroku nahra udaje do ineho pola a prida na koniec riadku separator
a v druhom kroku to prepise naspat do stareho pola*/

void acol(char ulozisko[], char separator)
{
  char fake_ulozisko[max_lenght];
  int pocet_delimov = 0;
  int i = 0;

  //funkcia, ktora zapisuje stare pole do noveho a na konci prida stlpec 
  while(ulozisko[i] > '\0')
  {
    if(ulozisko[i] != '\n' && ulozisko[i] != '\0')
    {
      fake_ulozisko[i + pocet_delimov] = ulozisko[i];
    }
    else if(ulozisko[i] == '\n') 
    {
      fake_ulozisko[i + pocet_delimov] = separator;
      fake_ulozisko[i + 1 + pocet_delimov] = '\n';
      pocet_delimov++;   
    }
    else if(ulozisko[i] == '\0')
    {
      fake_ulozisko[i + pocet_delimov] = separator;
      fake_ulozisko[i + 1 + pocet_delimov] = '\0';	      
    } 
    i++;
  } 

  //funckia ktora prepise z noveho do stareho abz sme to nakonci vedeli precitat
  int dlzka = (int)strlen(fake_ulozisko) + 1;
  for(int j = 0; j < dlzka ; j++)
    ulozisko[j] = fake_ulozisko[j];	  
  return;
}	

//funckia prida na koniec suboru jeden riadok
void arow(char ulozisko[], char separator)
{
  int i = (int)strlen(ulozisko);

  ulozisko[i] = separator;
  ulozisko[i + 1] = '\n';
  ulozisko[i + 2] = '\0';
  return;
}

/*funcia icol pridava stlpec podla toho kde ho chceme pridat*/

void icol(char ulozisko[], char separator, char poradie[])
{
  int riadok = atoi(poradie);
  char fake_ulozisko[max_lenght];
  int pocet_delimov = 0;
  int i = 0;
  int pocet_riadkov = 1;
  
  //funckia nastavi stlpec
  while(ulozisko[i] > '\0')
  {
    if(riadok == 1)
    {
      fake_ulozisko[0] = separator;
      if(ulozisko[i] == '\n')
      {
        fake_ulozisko[i + 1 + pocet_delimov] = '\n';
	fake_ulozisko[i + 2 + pocet_delimov] = separator;
	pocet_delimov++;
      }  	      
      else
	fake_ulozisko[i + 1 + pocet_delimov ] = ulozisko[i];       
    }
    else
    {
     if(ulozisko[i] == separator)
     {
       if(riadok - pocet_riadkov == 1)
       {
	 fake_ulozisko[i + pocet_delimov] = ulozisko[i];      
         fake_ulozisko[i + 1 + pocet_delimov] = separator;
	 pocet_delimov++;
	 pocet_riadkov++;
       }
       else
       {       
	fake_ulozisko[i + pocet_delimov] = ulozisko[i];
        pocet_riadkov++;
       }	
     }
     else if(ulozisko[i] == '\n')
     {
       fake_ulozisko[i + pocet_delimov] = ulozisko[i];
       pocet_riadkov = 1;
     }	     
     else
       fake_ulozisko[i + pocet_delimov] = ulozisko[i];     
    }	    
  i++;    
  }
  int dlzka = (int)strlen(fake_ulozisko) + 1;
  //funkcia prepise z vedlajsiho pola udaje do vystupneho subora
  for(int j = 0; j < dlzka ; j++)
    ulozisko[j] = fake_ulozisko[j];
  return;
}

//funckia prida riadok na miesto ktore zadame 
void irow(char ulozisko[], char separator, char poradie[])
{	
  int riadok = atoi(poradie);
  int pocet_riadkov = 0;
  int sep = 0;
  char fake_ulozisko[max_lenght];
  int i = 0;

  //funckii sme zadali miesto kde treba pridat riadok a tato funkcia ho prida na konkretne miesto
  while(ulozisko[i] > '\0')
  {
    if(riadok - pocet_riadkov  == 1)
    {
      fake_ulozisko[i] = separator;
      fake_ulozisko[i + 1 ] = '\n';
      fake_ulozisko[i + 2] = ulozisko[i];
      pocet_riadkov++;
      sep = 2 + sep;   
    }
    else if(ulozisko[i] == '\n')
    {	   
      pocet_riadkov++;
      fake_ulozisko[i + sep] = '\n';
    }  
    else	   
      fake_ulozisko[i + sep] = ulozisko[i]; 
  i++;      
  }
  int dlzka =(int)strlen(fake_ulozisko) + 1;
  for(int j = 0; j < dlzka; j++)
    ulozisko[j] = fake_ulozisko[j];
  return;  
}

//funkcia odstrani riadok , ktory jej zadame
void drow(char ulozisko[], char poradie[])
{
  int riadok = atoi(poradie);
  int i = 0;
  char fake_ulozisko[max_lenght];
  int pocet_riadkov = 0;
  int pocet_char = 0;

  //funckia bude zapisoavat subor do noveho pola a ked narazi na stlpec ktory ma odstranit tak to nenepise do noveho pola
  //a tym padaom ked prepiseme nove pole do stareho tak tam tie riadky nebudu
  while(ulozisko[i] > '\0')
  {
    if(riadok - pocet_riadkov == 1)
    {
      if(ulozisko[i] == '\n')
      {
        pocet_riadkov++;
	pocet_char++;
      }	
      else
        pocet_char++;	       
    }
    else if(ulozisko[i] == '\n')
    {	    
      fake_ulozisko[i - pocet_char] = '\n';
      pocet_riadkov++;
    }  
    else
      fake_ulozisko[i - pocet_char] = ulozisko[i];
  i++;    
  }
  int dlzka =(int)strlen(fake_ulozisko) + 1;
  for(int j = 0; j < dlzka; j++)
    ulozisko[j] = fake_ulozisko[j];
  return;  
}

/*funkcii ked zadame dva parametre take iste funguje ako funkcia drow
ale ked jej zadame rozdielne parametre tak odstrani vsetky riadky od prveho parametru az po druhy*/
void drows(char ulozisko[], char por_1[], char por_2[])
{
  int riadok_1 = atoi(por_1);
  int riadok_2 = atoi(por_2);
  int a = riadok_1;
  int b = riadok_2;	  
  char fake_ulozisko[max_lenght];
  int pocet_riadkov = 0;
  int pocet_char = 0;
  int i = 0;
  
  if(a == b)
  {	  
     drow(ulozisko, por_1);
     return;
  }   
  else
  {
    while(ulozisko[i] > '\0')
    {
      if((riadok_1 <= riadok_2) && riadok_1 - pocet_riadkov == 1)
      {
         if(ulozisko[i] == '\n')
	 {	
            pocet_char++;
            pocet_riadkov++;
	    riadok_1++;
         }
 	 else
	 {
	   pocet_char++;
	 }	 
      }
      else if(ulozisko[i] == '\n')
      {
        fake_ulozisko[i - pocet_char] = '\n';
        pocet_riadkov++;
      } 
      else
        fake_ulozisko[i - pocet_char] = ulozisko[i];
    i++;     
    }
  } 

  int dlzka = (int)strlen(fake_ulozisko) + 1;
  for(int j = 0; j < dlzka; j++)	  
    ulozisko[j] = fake_ulozisko[j];  
  
  return;	  
}	

/*funckia funguje skoro ako funkcia drow ale tato funkcia neodstranuje riadky ale stlpce*/
void dcol(char ulozisko[], char separator, char poradie[])
{
  char fake_ulozisko[max_lenght];
  int stlpec_min = atoi(poradie);
  int pocet_delimov = 0;
  int i = 0;
  int pocet_sep = 1;
  while(ulozisko[i] > '\0')
  {
    if(ulozisko[i] == separator && stlpec_min == pocet_sep)
    {
      pocet_sep++;
      pocet_delimov++;
    }
    else if(ulozisko[i] == separator)
    {
      fake_ulozisko[i - pocet_delimov] = ulozisko[i];
      pocet_sep++;
    }
    else if(ulozisko[i] == '\n')
    {
      fake_ulozisko[i - pocet_delimov] = '\n';
      pocet_sep = 1;
    }	    
    else
      fake_ulozisko[i - pocet_delimov] = ulozisko[i];
  i++;    
  }

  int dlzka =(int)strlen(fake_ulozisko) + 1;
  for(int j = 0; j < dlzka; j++)
    ulozisko[j] = fake_ulozisko[j];
  return;  
}       	

/*funkcia ked jej dame jeden parameter ktory je rovnky ako druhy, tak sa chova ako dcol
 ale ked jej dame dva rozdielne parametry tak odstrani stlpce od prveho po druhy*/
void dcols(char ulozisko[], char separator, char stlpec_1[], char stlpec_2[])
{
  char fake_ulozisko[max_lenght];
  int stlpec_from = atoi(stlpec_1);
  int stlpec_to = atoi(stlpec_2);
  int i = 0;
  int pocet_delimov = 0;
  int pocet_sep = 1;
  if(stlpec_to == stlpec_from)
  {
    dcol(ulozisko, separator, stlpec_1);
    return;	    
  }
  else
  {	  
    while(ulozisko[i] > '\0')
    {
      if(ulozisko[i] == separator && stlpec_from == pocet_sep)
      {  
        if(stlpec_from > stlpec_to)
          pocet_sep++;
        else
          pocet_delimov++;	       
      }
      else if(ulozisko[i] == separator)
      {
        fake_ulozisko[i - pocet_delimov] = ulozisko[i];
        pocet_sep++;
      }
      else if(ulozisko[i] == '\n')
      {
        fake_ulozisko[i - pocet_delimov] = ulozisko[i];
        pocet_sep = 1;
      }
      else
        fake_ulozisko[i - pocet_delimov] = ulozisko[i];
    i++;  
    }
  }  

  int dlzka = (int)strlen(fake_ulozisko) + 1;
  for(int j = 0; j < dlzka; j++)
    ulozisko[j] = fake_ulozisko[j];
  return;  
}

/*funkcia dostane riadok a nasledne podla toho ako cislo sme zadali tak zmeni kontretnu bunku na male pismena*/
void male_pis(char fake_ulozisko[], char separator, char stlp[])
{
  int stlpec = atoi(stlp);
  int actual_stlp = 1;
  int dlzka = (int)strlen(fake_ulozisko) + 1;
  
  //cyklus , ktory zmeni pozadovane pismena 
  for(int i = 0; i < dlzka; i++)
  {
    if(stlpec == actual_stlp)
    {	    	
      if(fake_ulozisko[i] == separator)
      {	      
	fake_ulozisko[i] = separator;
	actual_stlp++;
      }	
      else
        fake_ulozisko[i] = tolower(fake_ulozisko[i]);
    }
    else 
    {
      if(fake_ulozisko[i] == '\n')
      {
        fake_ulozisko[i] = '\n';
	actual_stlp = 1;	
      }
      else if(fake_ulozisko[i] == '\0')
        fake_ulozisko[i] = '\0';
      else if(fake_ulozisko[i] == separator)
      {
        fake_ulozisko[i] = separator;
	actual_stlp++;
      }
      else
	fake_ulozisko[i] = fake_ulozisko[i];      
    }	    
  }

return;
}

/*fukcia dostane riadok a nasledne podla toho ake cislo sme zadali tak zmeni konkretnu bunku na velke pismena*/
void velke_pis(char fake_ulozisko[], char separator, char stlp[])
{
  int stlpec = atoi(stlp);
  int actual_stlp = 1;
  int dlzka = (int)strlen(fake_ulozisko) + 1;
   
  //cyklus, ktory zmeni pozadovane pismena 
  for(int i = 0; i < dlzka; i++)
  {
    if(stlpec == actual_stlp)
    {
      if(fake_ulozisko[i] == separator)
      {
        fake_ulozisko[i] = separator;
	actual_stlp++;
      }	
      else
	fake_ulozisko[i] =toupper( fake_ulozisko[i]);      
    }
    else
    {
      if(fake_ulozisko[i] == '\n')
      {
        fake_ulozisko[i] = '\n';
	actual_stlp = 1;
      }	   
      else if(fake_ulozisko[i] == '\0')
        fake_ulozisko[i] = '\0';
      else if(fake_ulozisko[i] == separator)
      {
        fake_ulozisko[i] = separator;
	actual_stlp++;
      }	  
      else
	fake_ulozisko[i] = fake_ulozisko[i];      
    }	    
  }
return;
}	
	
/*funckia rows funguje tak ze do nove ulozisko nahrame riadky , ktore chceme menit a nasledne podla toho 
 aky argument zadame za argumentom rows tak sa zavola prislusna funckia */
void rows(char ulozisko[], char separator, char riadok_1[], char riadok_2[], char *argv[], int argc)
{
  char fake_ulozisko[max_lenght];
  int riadok_min = atoi(riadok_1);
  int riadok_min_2 = riadok_min;
  int riadok_max = atoi(riadok_2);
  int pocet_riadkov = 0;
  int pocet_n = 0;
  int i = 0;
  int pocet_char = 0;  //pocet charov ktore musime odstranit aby sme dostali konktrente riadky
  int pocet_char_2 = 0; //pocet charov ktore musime pridat aby sme riadky vratili na prislusne miesto
  int pocet_riadkov_n2 = 0;
  int dlzka2 = (int)strlen(ulozisko) + 1;

  for(int n = 0; n < dlzka2; n++)
  {
    if(ulozisko[n] == '\n')
      pocet_n++;	    
  }	  
 
   //funkcia ktora nahra do pola tie riadky z ktorymi chceme robit
   while(ulozisko[i] > '\0')
   {
     if(*riadok_1 != '-')
     {	    
       if(((riadok_min - pocet_riadkov == 1) && ((riadok_min <= atoi(riadok_2)) || (*riadok_2 == '-'))) && *riadok_1 != '-')
       {
         if(ulozisko[i] == '\n')
	 {
	   fake_ulozisko[i - pocet_char] = '\n';
	   pocet_riadkov++;
	   riadok_min++;
	 }
	 else if(ulozisko[i] == '\0')
	   fake_ulozisko[i - pocet_char] = '\0';   	        
	 else
           fake_ulozisko[i - pocet_char] = ulozisko[i];	       
       }
       else if(ulozisko[i] == '\0')
       {
         fake_ulozisko[i - pocet_char] = '\0';
       }   
       else
       {
          if(ulozisko[i] == '\n')
	  {
            pocet_riadkov++;
	    pocet_char++;
	  }
	  else
            pocet_char++;	       
       }
     }
     else
     {
       if((pocet_n - 1) != pocet_riadkov)	
       {	     
         if(ulozisko[i] == '\n')
         {
           pocet_riadkov++;
           pocet_char++;
         }	   
       else 
         pocet_char++;
      }	     
      else 
      {
        if(ulozisko[i] == '\0')
       	  fake_ulozisko[i - pocet_char] = '\0';
        else 
	  fake_ulozisko[i - pocet_char] = ulozisko[i];       
      }	     
    }	    
  i++;  
  }
  
  //funkcia ktora zisti aku funkcia ma zavolat podla zadanych parametrov
  for(int k = 1; k < argc; k++)
  {
    if(strcmp(argv[k], "cset") == 0)
    { 
	    // cset(fake_ulozisko, separator, argv[k + 1]);	    
    }
    else if(strcmp(argv[k], "tolower") == 0)	    
      male_pis(fake_ulozisko, separator, argv[k + 1]);	  
    else if(strcmp(argv[k], "toupper") == 0)
      velke_pis(fake_ulozisko, separator, argv[k + 1]);	    
  }
  
  
  //funckia ktora nasledne nahra uz vymenenne riadky na svoje miesto
  int dlzka = (int)strlen(ulozisko) + 1;
  for(int j = 0; j < dlzka; j++)
  {
    if(*riadok_1 != '-')
    {	    
      if((riadok_min_2 - pocet_riadkov_n2 == 1 && riadok_min_2 <= riadok_max) || *riadok_2 == '-') 
      { 
        if(ulozisko[j] == '\n')
        {
  	  ulozisko[j] = '\n';      
          riadok_min_2++;
	  pocet_riadkov_n2++;
        }
        else if(ulozisko[j] == '\0')
	  ulozisko[j] = '\0';
        else      
          ulozisko[j] = fake_ulozisko[j - pocet_char_2];
      }	
      else
      {
        if(ulozisko[j] == '\n')
        {
          ulozisko[j] = '\n';
	  pocet_riadkov_n2++;
	  pocet_char_2++;
        }	
        else if(ulozisko[j] == '\0')      
  	  ulozisko[j] = '\0';
        else
        {	      
          ulozisko[j] = ulozisko[j]; 
          pocet_char_2++; 
        } 	
      }
    }
    else
    {
      if((pocet_n - 1) != pocet_riadkov_n2)
      {
        if(ulozisko[j] == '\n')
 	{
	  pocet_riadkov_n2++;
	  pocet_char_2++;
	}
        else
	  pocet_char_2++;	
      }
      else
      {
        if(ulozisko[j] == '\0')
	  ulozisko[j] = '\0';
	else
	  ulozisko[j] = fake_ulozisko[j - pocet_char_2];	 
      }	      
    }	    
  }		  
  return;
}	

int main(int argc,char *argv[])
{	
  char ulozisko[max_lenght] ; // pole v ktorom je ulozeny cely subor
  int sk_velkost = 0; 

  save(sk_velkost, ulozisko);  
  char separator = delimeter(argc, argv, ulozisko); 
  
  //funckia ktora sa pozrie na vsetky argumenty a vyberie funkciu ktoru pozaduejem
  for(int i = 1; i < argc; i++)
  {
    if(strcmp(argv[i], "acol") == 0)
    {
      acol(ulozisko, separator);
    }
    else if(strcmp(argv[i], "arow") == 0)
    {
      arow(ulozisko, separator);
    }
    else if(strcmp(argv[i], "icol") == 0)
    { 
      int ico = 0;
      int incr = 0;
      while(ulozisko[incr] != '\n')
      {
        if(ulozisko[incr] == separator)
        {
	  ico++;
	  incr++;
	}
        else
	  incr++;
       }  	
      if((ico + 1) < atoi(argv[i + 1]))
      {
        printf("Zadali ste viac stlpcov ako je v programe!\n");
        return 1;  
     }
     else	      
         icol(ulozisko, separator ,argv[i + 1]);
    }
    else if(strcmp(argv[i], "irow") == 0)
    { 
      int ir = atoi(argv[i + 1]);	
      if(ir < 1) 
      {
        printf("cislo v argumente musi byt vacsie ako 0!\n");
        return 1;
      }
      else      
        irow(ulozisko, separator, argv[i + 1]);
    }
    else if(strcmp(argv[i], "drow") == 0)
    {
       int dr = atoi(argv[i + 1]);
       if(dr < 1)
       {
         printf("cislo v argumente musi byt vacsie ako 0!\n");
	 return 1;
       }	
       else       
         drow(ulozisko, argv[i + 1]);
    }
    else if(strcmp(argv[i], "drows") == 0)
    {
       int d_1 = atoi(argv[i + 1]);
       int d_2 = atoi(argv[i + 2]);
       if(d_1 > d_2)
       {
         printf("Argument prvy v drows musi byt mensie ako druhy!\n");
	 return 1;	
       } 
       else
         drows(ulozisko, argv[i + 1], argv[i + 2]);
    }
    else if(strcmp(argv[i], "dcol") == 0)
    { 
       int pd = 0;
       int in = 0;
       while(ulozisko[in] != '\n')
       {
	 if(ulozisko[in] == separator)
         {
           in++; 
           pd++;
	 }  
	 else
	   in++;
      }      
      if(pd < atoi(argv[i + 1]))
      {
         printf("Zadali ste vacsi argument ako je v skutocnosti slpcov!\n");
	 return 1;
      }	 	     		
      else
         dcol(ulozisko, separator, argv[i + 1]);
    }
    else if(strcmp(argv[i], "dcols") == 0)
    { 
       int dc_1 = atoi(argv[i + 1]);
       int dc_2 = atoi(argv[i + 2]);	      
       int dc = 0;
       int inc = 0;
       if(dc_1 > dc_2)
       {
          printf("Argumnet prvy  v dcols musi byt mensi ako druhy!\n");
	  return 1;
       }	
       else
       {	      
          while(ulozisko[inc] != '\n')
          { 
            if(ulozisko[inc] == separator)
	    {
	      inc++;
	      dc++;
	    }
            else 
	      inc++;	
          }	
       if(dc < atoi(argv[i + 2]))
       {
          printf("Zadali ste vacsi argument ako je v skutocnosti slpcov\n");
	  return 1;
        }
        else 
           dcols(ulozisko, separator, argv[i + 1], argv[i + 2]);
      }	
    }
    else if(strcmp(argv[i], "rows") == 0)
    {
      rows(ulozisko, separator, argv[i + 1], argv[i + 2], argv , argc);
    }
  }	 

printf("%s",ulozisko);
 
  return 0;
}
