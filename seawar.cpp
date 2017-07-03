#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>

void gotoxy(int x,int y);//������ƶ� 
int choose_menu();//��ʼ����ѡ��˵� 
int choose_boat();//ѡ���ƶ�ս�� 
void butt_des();//����˵������ 
void show_menu();//��ʼ�˵����� 
void start_game(int t);//��ʼ��Ϸ���� 
void restart();//���¿�ʼ��Ϸ 
void move(int type,int a,int b);//���ս������ 
void game_des();//��Ϸ˵������ 
void com_rand();//����ս������ 
void open_fire();//������ɺ��ڽ��� 
void com_fire(int xy);//���Կ���
void fire();//��ҿ��� 
void push(int item1,int item2);//�������� 
void pop();//ɾ������ 
int search(int n,int direction);//��������������չ
void write_data(int xy,int i); //���ļ��м�¼�������꼰�Ƿ���� 

/*
����˵��
0.��������ע��show_menu()����
1.���������е���test()
*/
void test();//ר���������Ե���������ڹ��� 
void test_com_fire(int i);
void test_fire();

//��������Ϣ�ĵ�ͼ 
int map[12][12]={ 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
				  8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 8,
				  8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 8,
				  8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 8,
				  8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 8,
				  8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 8,
				  8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 8,
				  8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 8,
				  8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 8,
				  8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 8,
				  8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 8,
				  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8};


//��ŵ�����Ϣ�ĵ�ͼ				  
int map_com[12][12]={ 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
					  8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 8,
				      8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 8,
				      8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 8,
				      8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 8,
				      8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 8,
				      8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 8,
				      8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 8,
				      8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 8,
				      8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 8,
				      8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 8,
				      8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8};
				      

//ս��ѡ�����С��ͷ�ĳ�ʼyֵ 
int flo=16;
//��¼��ҿ��ڵ���� 
int chx=1,chy=1;

//ս����Ϣ 
typedef struct boat{
	int length;//���� 
	int state;//���� 
	int x;//x���� 
	int y;//y���� 
}Boat;
Boat boat[5]={{2,0,0,0},{3,0,0,0},{3,0,0,0},{4,0,0,0},{5,0,0,0}};

//ջ�Ķ��� 
typedef struct stack{
	int coord;
	int next;
}Stack;
//topΪջ������ 
int top=-1;
Stack boat_attacked[20];

void write_data(int xy,int i){
	FILE *fp;
	fp=fopen("boat.txt","a+");//��׷����ʽд�� 
	fprintf(fp,"%d,%d",xy/10+1,xy%10+1);
	switch(i){
		case -1:fprintf(fp,"--δ����\n");break;
		case 0:fprintf(fp,"--����\n");break;
	}
	fclose(fp);
}

void push(int item1,int item2){
	top++;
	boat_attacked[top].coord=item1;
	boat_attacked[top].next=item2;
}

void pop(){
	boat_attacked[top].next=-1; 
	top--;
}

int search(int n,int direction){
	switch(direction){
		case 0://�� 
			if(n%10==0)
				return n;
			else
				return n-1;
			break;
		case 1://�� 
			if(n%10==9)
				return n;
			else
				return n+1;
			break;
		case 2://�� 
			if(n/10==0)
				return n;
			else
				return n-10;
			break;
		case 3://�� 
			if(n/10==9)
				return n;
			else
				return n+10;
			break;
	}
}

void test_com_fire(int xy){
	//xy/10==x   xy%10==y;
	static int num=0;
	int i,j,k,next,n=0;
	if(top==16){
		printf("test finish\n");
		printf("%d",num);
		getch();
		exit(0); 
	}
	if(xy==-1){
		xy=rand()%100;
		if(num<50)
		do
			xy=rand()%100;
		while((xy/10%2+xy)%2!=0);
	}	
	if(map[xy/10+1][xy%10+1]==1)
		test_com_fire(-1);
	push(xy,-1);
	if(map[xy/10+1][xy%10+1]==-1){
		printf("%d,%d--δ����\n",xy/10+1,xy%10+1);
		map[xy/10+1][xy%10+1]=1;
		num++;
		pop();
		test_fire();
		test_com_fire(-1);
	}
	if(map[xy/10+1][xy%10+1]==0){
		printf("%d,%d--����",xy/10+1,xy%10+1);
		map[xy/10+1][xy%10+1]=1;
		num++;
		next=-1;
		j=k=boat_attacked[top].coord;
		printf("��ʼkΪ%d,%d next=%d\n",k/10+1,k%10+1,next);
	while(next<4){
		next++;
		j=k;
		while(map[search(j,next)/10+1][search(j,next)%10+1]==0){
			map[search(j,next)/10+1][search(j,next)%10+1]=1;
			printf("%d,%d--���� next=%d",search(j,next)/10+1,search(j,next)%10+1,next);
			push(search(j,next),next);
			j=boat_attacked[top].coord;
			if(map[search(j,next)/10+1][search(j,next)%10+1]==-1){
				printf("%d,%d--δ����+ next=%d\n",search(j,next)/10+1,search(j,next)%10+1,next);
				map[search(j,next)/10+1][search(j,next)%10+1]=1;
				num++;
				test_fire();
		}
		}
		if(map[search(k,next)/10+1][search(k,next)%10+1]==-1){
			printf("%d,%d--δ����= next=%d\n",search(k,next)/10+1,search(k,next)%10+1,next);
			map[search(k,next)/10+1][search(k,next)%10+1]=1;
			num++;
			test_fire();
		}
	}
	for(i=-1;i<top;i++)
		boat_attacked[i].next=4;
	test_com_fire(-1);
}
}

void com_fire(int xy){
	//xy/10==x   xy%10==y;
	//numΪ���ڴ��� 
	static int num=0;
	int i,j,k,next,n=0;
	//������ȫ�����к� 
	if(top==16){
		system("cls"); 
		printf("you lose\n");
		printf("�����������");
		getch();
		//����ѡ������һ�ֻ��˳� 
		printf("����r�����q�˳�");
		switch(getch()){
			case 'r':
				restart();
				break;
			case 'q':exit(0);
			default:exit(0);
		} 
	}
	//���������Ϊ-1ʱ��Ϊ������� 
	//�������ʱ����ǰ50�ڲ������������ԭ��  ���ӻ��и��� 
	if(xy==-1){
		xy=rand()%100;
		if(num<50)
		do{
			xy=rand()%100;
		}
		while((xy/10%2+xy)%2!=0);
	}
	//�����ڴ��Ѵ��������ʱ��������� 
	if(map[xy/10+1][xy%10+1]==1)
		com_fire(-1);
		//����������ջ 
	push(xy,-1);
	//��δ���� ���ڽ�������ʾ ��д���ļ� ���ڵ�ͼ�м�¼ �������ջ 
	if(map[xy/10+1][xy%10+1]==-1){
		gotoxy(xy/10+16,xy%10+1);
		printf("-");
		write_data(xy,-1);
		map[xy/10+1][xy%10+1]=1;
		num++;
		pop();
		fire();
		com_fire(-1);
	}
	//������ 
	if(map[xy/10+1][xy%10+1]==0){
		gotoxy(xy/10+16,xy%10+1);
		printf("+");
		write_data(xy,0);
		num++;
		map[xy/10+1][xy%10+1]=1;
		next=-1;
		//k���³�ʼ��������  j��Ϊ̽������
		j=k=boat_attacked[top].coord;
		//̽��������������� 
	while(next<4){
		next++;
		j=k;
		//�����������ĳһ�����Ա�����  ����ȱ����÷���  ֱ�����е��������ǽ���ѻ���������  �������еĴ���������ջ 
		while(map[search(j,next)/10+1][search(j,next)%10+1]==0){
			map[search(j,next)/10+1][search(j,next)%10+1]=1;
			gotoxy(search(j,next)/10+16,search(j,next)%10+1);
			printf("+");
			write_data(search(j,next),0);
			push(search(j,next),next);
			j=boat_attacked[top].coord;
			if(map[search(j,next)/10+1][search(j,next)%10+1]==-1){
			gotoxy(search(j,next)/10+16,search(j,next)%10+1);
			printf("-");
			write_data(search(j,next),-1);
			map[search(j,next)/10+1][search(j,next)%10+1]=1;
			num++;
			fire();
		}
		}
		if(map[search(k,next)/10+1][search(k,next)%10+1]==-1){
			gotoxy(search(k,next)/10+16,search(k,next)%10+1);
			printf("-");
			write_data(search(k,next),-1);
			num++;
			map[search(k,next)/10+1][search(k,next)%10+1]=1;
			boat_attacked[top].next=next;
			fire();
		}
	}
	for(i=-1;i<top;i++)
		boat_attacked[i].next=4;
	com_fire(-1);
}
}

void test_fire(){
	printf("huamn's turn\n");
}

void fire(){
	static int flag;
	flag=1;//flag����Ϊ�ж��Ƿ������ҿ��� 
	gotoxy(chx,chy);
	while(flag)
	switch(getch()){
		case 13:
			int win;
			win=0;
			//����һ��� 
			if(map_com[chx][chy]==0){
					gotoxy(chx,chy);
					printf("+");
					//���Ե�ͼ�ϼ��±����е�����
					map_com[chx][chy]=2;
					//����������ͼ�ж��Ƿ�����ѻ�ʤ 
					for(int x=1;x<11;x++)
						for(int y=1;y<11;y++)
							if(map_com[x][y]==2)
								win++;
							if(win==17){
							system("cls");
							printf("you win\n");
							getch();
							printf("����r�����q�˳�");
							switch(getch()){
								case 'r':
									restart();
									break;
								case 'q':exit(0);
								default:exit(0);
							}
						}
						//�������� 
					fire();
				}
				//��δ���� 
			if(map_com[chx][chy]==-1){
					gotoxy(chx,chy);
					printf("-");
					map_com[chx][chy]=1;
					if(top==-1)//������ǵ�һ��ʱ������������ 
					com_fire(-1);
					//�������������  ���Ի�����δ���е�����¿��ڵ�  ������˴ο����õ��Ը��ݻ���������ڶ�������� 
					if(boat_attacked[top].next!=4){
					flag=0;
					break;
				}
				//�����ֵ�����������ڵ�  ���ٴ��õ���������� 
				com_fire(-1);
				}
			else
				break;	
		case 224:
     		switch(getch()){
        		case 72:
        			gotoxy(chx,chy);
        			if(map_com[chx][chy]<1)
        			printf(" ");
        			if(chy==1)
        			chy=11;
			        gotoxy(chx,--chy);
			        if(map_com[chx][chy]<1)
			        printf("*");
			        break;
		        case 80:
        			gotoxy(chx,chy);
        			if(map_com[chx][chy]<1)
        			printf(" ");
		        	if(chy==10)
        			chy=0;
		        	gotoxy(chx,++chy);
		        	if(map_com[chx][chy]<1)
		            printf("*");
		            break;
		        case 75:
        			gotoxy(chx,chy);
        			if(map_com[chx][chy]<1)
        			printf(" ");
					if(chx==1)
        			chx=11; 
		            gotoxy(--chx,chy);
		            if(map_com[chx][chy]<1)
		            printf("*");
		            break;
		         case 77:
        			gotoxy(chx,chy);
        			if(map_com[chx][chy]<1)
        			printf(" ");
		         	if(chx==10)
        			chx=0;
		            gotoxy(++chx,chy);
		            if(map_com[chx][chy]<1)
		            printf("*");
		            break;   
		     }       
		}
}

void com_rand(){
	int i,num,flag=0;
	srand(time(0));
	//flagΪ������Ĵ�������  ��ȫ�����������˳����� 
	while(flag<5){
		num=rand()%200+100;//����һ��100-299�������  ��λ�������  ʮλ����ͷ������  ��λ����ͷ������ 
		if(num/100==1){
			if(num/10%10>10-boat[flag].length)//����ͷ���ϴ�����Խ���߽�  ���������� 
				continue;
			for(i=0;i<boat[flag].length;i++)//�����ص�  �˳�ѭ�� 
				if(map_com[num/10%10+1+i][num%10+1]==0)
					break;
				if(i<boat[flag].length)//������ѭ��Ϊ��;�˳���  ���������� 
					continue;
			for(i=0;i<boat[flag].length;i++){ 
				map_com[num/10%10+1+i][num%10+1]=0;
			//	printf("map[%d][%d]\n",num/10%10+i,num%10+1);
				} 
		}
		if(num/100==2){
			if(num%10>10-boat[flag].length)
				continue;
			for(i=0;i<boat[flag].length;i++)
				if(map_com[num/10%10+1][num%10+1+i]==0)
					break;
				if(i<boat[flag].length)
					continue;
			for(i=0;i<boat[flag].length;i++){ 
				map_com[num/10%10+1][num%10+1+i]=0;
			//	printf("map[%d][%d]\n",num/10%10+1,num%10+1+i);
				}
		}
		flag++;
	}
}

//����ƶ����� 
void gotoxy(int x,int y)
{
	HANDLE hout;
	COORD coord;
	coord.X=x;
	coord.Y=y;
	hout=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hout,coord);
}

//move�������ƶ�ս���Ĺؼ����� 
//typeΪ����ս�����ͺ�  aΪ��ͷx���� bΪ��ͷy���� 
void move(int type,int a,int b){
	int x=a,y=b;
	int i=0;
	int flag=0,flag2=0;//flag������ǵ���תʱ�Ƿ��ײǽ��ײ��ս��  flag2��������ƶ�ʱ�Ƿ��ײǽ��ײ��ս�� 
	while(1)
	switch(getch()){
		
		//�����س�ʱ 
		case 13:start_game(1);break;
		
		//�����ո�ʱ 
		case 32:
			//�����֮ǰΪ�����Ϊ��  ���Ϊ�����Ϊ�� 
			boat[type].state=boat[type].state==0;
			flag=0;
			if(boat[type].state==1){
				for(i=1;i<boat[type].length;i++)
				//��������һ����ײ��ǽ��ս��ʱ ����flag���˳�ѭ�� 
					if(y>11-boat[type].length||map[x][y+i]==0){
						gotoxy(0,16);
						flag=6;
						break;
					}
					//����flagʱ ��תʧЧ  ���˳��˴���ת 
					if(flag==6){
						boat[type].state=boat[type].state==0;
						break;
					} 
				for(i=1;i<boat[type].length;i++){
					//�����תǰ�Ĵ�����ʾ���ڵ�ͼ����Ϊ�� 
			    	gotoxy(x+i,y);
			    	printf(" ");
			    	map[x+i][y]=-1;
			    	//��ʾ��ת��Ĵ��� 
			        gotoxy(x,y+i);
			        printf("X");
			        map[x][y+i]=0;
				}
			}
			if(boat[type].state==0){
				for(i=1;i<boat[type].length;i++)
					if(x>11-boat[type].length||map[x+i][y]==0){
						gotoxy(0,16);
						flag=6;
						break;
					}
					if(flag==6){
						boat[type].state=boat[type].state==0;
						break;
					}
				for(i=1;i<boat[type].length;i++){
			        gotoxy(x,y+i);
			        printf(" ");
			        map[x][y+i]=-1;
			        gotoxy(x+i,y);
			        printf("X");
			        map[x+i][y]=0;
				}
			}
			break; 
			
		//������������ʱ 
		case 224:                    
			switch(getch()){
				//�� 
        		case 72:
        			flag2=0;
			        if(boat[type].state==0){
			        	for(i=0;i<boat[type].length;i++)
			        	//�����ײ�������� ������flag2���˳�ѭ�� 
							if(map[x+i][y-1<1?10:y-1]==0){
								flag2=6;
								break;
							}
							//��flag2ʱ �˳��˴��ƶ�����  �����ƶ� 
							if(flag2==6) break;
							//����ƶ�ǰ�Ĵ��� 
			        	for(i=0;i<boat[type].length;i++){
			        		gotoxy(x+i,y);
			        		printf(" ");
			        		map[x+i][y]=-1;
						}
			    		if(y==1) y=11;//�������߽�  �򴩹��߽絽���� 
						y--;
						//��ʾ�ƶ�֮��Ĵ��� 
			        	for(i=0;i<boat[type].length;i++){
			        		gotoxy(x+i,y);
			        		printf("X");
			        		map[x+i][y]=0;
						}
			    	}
			    	if(boat[type].state==1){
			    		for(i=0;i<boat[type].length;i++)
							if(map[x][y-1<1?10-i:y-1]==0){
								flag2=6;
								break;
							}
							if(flag2==6) break;
			        	for(i=0;i<boat[type].length;i++){
			        		gotoxy(x,y+i);
			        		printf(" ");
			        		map[x][y+i]=-1;
						}
			    		if(y==1) y=11-boat[type].length+1;
						y--;
			        	for(i=0;i<boat[type].length;i++){
			        		gotoxy(x,y+i);
			        		printf("X");
			        		map[x][y+i]=0;
						}
			    	}
			    	boat[type].x=x,boat[type].y=y;
			        break;
			    //�� 
		    	case 80:
		    		flag2=0;
		        	if(boat[type].state==0){
		        		for(i=0;i<boat[type].length;i++)
							if(map[x+i][y+1>10?1:y+1]==0){
								flag2=6;
								break;
							}
							if(flag2==6) break;
			        	for(i=0;i<boat[type].length;i++){
			        		gotoxy(x+i,y);
			        		printf(" ");
			        		map[x+i][y]=-1;
						}
			    		if(y==10) y=0;
						y++;
			        	for(i=0;i<boat[type].length;i++){
			        		gotoxy(x+i,y);
			        		printf("X");
			        		map[x+i][y]=0;
						}
			    	}
			    	if(boat[type].state==1){
			    		for(i=0;i<boat[type].length;i++)
							if(map[x][y+boat[type].length>10?i+1:y+boat[type].length]==0){
								flag2=6;
								break;
							}
							if(flag2==6) break;
			        	for(i=0;i<boat[type].length;i++){
			        		gotoxy(x,y+i);
			        		printf(" ");
			        		map[x][y+i]=-1;
						}
			    		if(y==11-boat[type].length) y=0;
						y++;
			        	for(i=0;i<boat[type].length;i++){
			        		gotoxy(x,y+i);
			        		printf("X");
			        		map[x][y+i]=0;
						}
			    	}
			        boat[type].x=x,boat[type].y=y;
					break;
				//�� 
				case 75:
					flag2=0;
		        	if(boat[type].state==0){
		        		for(i=0;i<boat[type].length;i++)
							if(map[x-1<1?10-i:x-1][y]==0){
								flag2=6;
								break;
							}
							if(flag2==6) break;
			        	for(i=0;i<boat[type].length;i++){
			        		gotoxy(x+i,y);
			        		printf(" ");
			        		map[x+i][y]=-1;
						}
			    		if(x==1) x=11-boat[type].length+1;
						x--;
			        	for(i=0;i<boat[type].length;i++){
			        		gotoxy(x+i,y);
			        		printf("X");
			        		map[x+i][y]=0;
						}
			    	}
			    	if(boat[type].state==1){
			    		for(i=0;i<boat[type].length;i++)
							if(map[x-1<1?10:x-1][y+i]==0){
								flag2=6;
								break;
							}
							if(flag2==6) break;
			        	for(i=0;i<boat[type].length;i++){
			        		gotoxy(x,y+i);
			        		printf(" ");
			        		map[x][y+i]=-1;
						}
			    		if(x==1) x=11;
						x--;
			        	for(i=0;i<boat[type].length;i++){
			        		gotoxy(x,y+i);
			        		printf("X");
			        		map[x][y+i]=0;
						}
			    	}
			    	boat[type].x=x,boat[type].y=y;
			        break;
			    //�� 
		        case 77:
		        	flag2=0;
		        	if(boat[type].state==0){
		        		for(i=0;i<boat[type].length;i++)
							if(map[x+boat[type].length>10?i+1:x+boat[type].length][y]==0){
								flag2=6;
								break;
							}
							if(flag2==6) break;
			        	for(i=0;i<boat[type].length;i++){
			        		gotoxy(x+i,y);
			        		printf(" ");
			        		map[x+i][y]=-1;
						}
			    		if(x==10-boat[type].length+1) x=0;
						x++;
			        	for(i=0;i<boat[type].length;i++){
			        		gotoxy(x+i,y);
			        		printf("X");
			        		map[x+i][y]=0;
						}
			    	}
			    	if(boat[type].state==1){
			    		for(i=0;i<boat[type].length;i++)
							if(map[x+1>10?1:x+1][y+i]==0){
								flag2=6;
								break;
							}
							if(flag2==6) break;
			        	for(i=0;i<boat[type].length;i++){
			        		gotoxy(x,y+i);
			        		printf(" ");
			        		map[x][y+i]=-1;
						}
			    		if(x==10) x=0;
						x++;
			        	for(i=0;i<boat[type].length;i++){
			        		gotoxy(x,y+i);
			        		printf("X");
			        		map[x][y+i]=0;
						}
			    	}
			    	boat[type].x=x,boat[type].y=y;
			        break;
		    }  
	}
}

//�������t�ǵ�������Ϸʱս����ʾΪĬ�ϲ��֣������ƶ�ʱ��Ȼʹ�ô˽��棬��ս������Ҫ�ٷ���Ϊ���β���ʱ��λ�ã�������ս����ʼλ�ò���
//t==0ʱս��ΪĬ�ϲ���  t!=1ʱ�̳��ϴβ��� 
void start_game(int t){
	int i,x,y;
	if(t==0){
		//ս����ʼ����  
	boat[0].x=1,boat[0].y=1;//��ͷ���� 
	for(i=1;i<3;i++) map[i][1]=0;//���ڵ�ͼռλ 
	
	boat[1].x=1,boat[1].y=2;
	for(i=1;i<4;i++) map[i][2]=0;
	
	boat[2].x=1,boat[2].y=3;
	for(i=1;i<4;i++) map[i][3]=0;
	
	boat[3].x=1,boat[3].y=4;
	for(i=1;i<5;i++) map[i][4]=0;
	
	boat[4].x=1,boat[4].y=5;
	for(i=1;i<6;i++) map[i][5]=0;
	
	system("cls");
	printf("------------\n");
	printf("|XX        |\n");
	printf("|XXX       |\n");
	printf("|XXX       |\n");
	printf("|XXXX      |\n");
	printf("|XXXXX     |\n");
	for(i=0;i<5;i++)
	printf("|          |\n");
	printf("------------\n");
	printf("\n\nѡ��ս���س����ƶ����ٰ��س�����\n\n");
	printf("  ��������(ռ2��)\n");
	printf("    ����(ռ3��)\n");
	printf("    Ǳͧ��(ռ3��)\n");
	printf("    ս�н�(ռ4��)\n");
	printf("    ����ĸ��(ռ5��)\n");
	printf("    ȷ�Ϸ������\n");
}
//���ݵ�ͼ��ʾս������ 
	for(x=1;x<11;x++)
			for(y=1;y<11;y++)
				if(map[x][y]==0){
					gotoxy(x,y);
					printf("X");
				}	
	switch(choose_boat()){
		case 0:gotoxy(boat[0].x,boat[0].y);move(0,boat[0].x,boat[0].y);break;
		case 1:gotoxy(boat[1].x,boat[1].y);move(1,boat[1].x,boat[1].y);break;
		case 2:gotoxy(boat[2].x,boat[2].y);move(2,boat[2].x,boat[2].y);break;
		case 3:gotoxy(boat[3].x,boat[3].y);move(3,boat[3].x,boat[3].y);break;
		case 4:gotoxy(boat[4].x,boat[4].y);move(4,boat[4].x,boat[4].y);break;
		case 5:com_rand();open_fire();break;
		//��ӡmap  gotoxy(0,40);for(i=0;i<12;i++) for(int j=0;j<12;j++) printf("%2d%c",map_com[j][i],j==11?'\n':' ');gotoxy(0,25);for(i=0;i<12;i++) for(int j=0;j<12;j++) printf("%2d%c",map[j][i],j==11?'\n':' ');
	}
}

int choose_boat(){
	int y=flo;
	while(1)
	switch(getch()){
		case 13:
			return y-16; 
   		case 224:                    
     		switch(getch()){
        		case 72:
        			gotoxy(2,y);
			        printf(" ");
			        if(y==16)//ָ�뵽��һ��ʱ�ٰ������������һ�� 
			        y=22;
			        gotoxy(2,y-=1);
			        printf("��");
			        flo=y;
			        break;
		        case 80:
		        	gotoxy(2,y);
			        printf(" ");
			        if(y==21)//ָ�뵽���һ��ʱ�ٰ�����������һ�� 
		        	y=15;
		        	gotoxy(2,y+=1);
		            printf("��");
		            flo=y;
		            break;
		     }
			 break;     
	}
}

int choose_menu(){
	int y=13; 
	while(1)
	switch(getch()){
		case 13:
			return y-13; 
   		case 224:                    
     		switch(getch()){
        		case 72:
        			gotoxy(14,y);
			        printf(" ");
			        if(y==13)
			        y=17;
			        gotoxy(14,y-=1);
			        printf("��");
			        break;
		        case 80:
		        	gotoxy(14,y);
			        printf(" ");
			        if(y==16)
		        	y=12;
		        	gotoxy(14,y+=1);
		            printf("��");
		            break;
		     }
			 break;   
	}
}

void open_fire(){
	int i;
	system("cls");
	
	//��ʾ��ҵ�ͼ (��)
	printf("------------\n");
	printf("|*         |\n");
	for(i=0;i<9;i++)
	printf("|          |\n");
	printf("------------\n");
	printf("\n���س���ȷ�Ͽ���");
	
	//��ʾ���Ե�ͼ (��)
	gotoxy(15,0);
	printf("------------");
	for(i=0;i<10;i++){
	gotoxy(15,1+i);
	printf("|          |");
} 
	gotoxy(15,11);
	printf("------------");
	
	//��ʾ��Ҳ��ú�ĵ�ͼ (��)
	gotoxy(30,0);
	printf("------------");
	for(i=0;i<10;i++){
	gotoxy(30,1+i);
	printf("|          |");
}
	gotoxy(30,11);
	printf("------------");
	for(i=0;i<12;i++) 
		for(int j=0;j<12;j++)
		if(map[j][i]==0){
			gotoxy(30+j,i);
			printf("X");
		}
/*  �������������ս������ 
	gotoxy(45,0);
	printf("------------");
	for(i=0;i<10;i++){
	gotoxy(45,1+i);
	printf("|          |");
}
	gotoxy(45,11);
	printf("------------");
	for(i=0;i<12;i++) 
		for(int j=0;j<12;j++)
		if(map_com[j][i]==0){
			gotoxy(45+j,i);
			printf("X");
		}
*/

		fire();
}

void game_des(){
	system("cls");
	int i;
	printf("________________________________________\n");
	printf("|                                      |\n");
	printf("|            ��ս��Ϸģ��              |\n");
	printf("|              (������)                |\n");
	printf("|                                      |\n");
	printf("|                                      |\n");
	printf("|                     |��              |\n");
	printf("|              _______|___             |\n");
	printf("|             ��        ��             |\n");
	printf("|               ��������               |\n");
	printf("|                                      |\n");
	printf("|                                      |\n");
	printf("|     ��Ϸ˵������Һ͵��Ը���������   |\n");
	printf("|     10 *10�������з���ս����ÿ����   |\n");
	printf("|     ��,�ҶԶԷ�����,�źú����ƶ�   |\n");
	printf("|     ÿ�Ҵ��ɺ���������õ����ܽӴ�   |\n");
	printf("|     �������ص���˫��������ը�Է���   |\n");
	printf("|     �н���ÿ�εĺ�ը�������ʾ����   |\n");
	printf("|     ��������ɼ���������δ��������   |\n");
	printf("|     ���Է���Ҫ����һ��ս����Ҫ����   |\n");
	printf("|     �������и��ӣ���ϷĿ�����ڶ���   |\n");
	printf("|     ֮ǰ���Է�ս��ȫ��������         |\n");
	printf("|                                      |\n");
	printf("|           (�������������˵�)         |\n");
	printf("����������������������������������������");
	while(1)
	switch(getch()){
   		case 224:                    
     		switch(getch()){
        		case 75:
        			show_menu();
        	}
	}
}

void butt_des(){
	system("cls");
	int i;
	printf("________________________________________\n");
	printf("|                                      |\n");
	printf("|            ��ս��Ϸģ��              |\n");
	printf("|              (������)                |\n");
	printf("|                                      |\n");
	printf("|                                      |\n");
	printf("|                     |��              |\n");
	printf("|              _______|___             |\n");
	printf("|             ��        ��             |\n");
	printf("|               ��������               |\n");
	printf("|                                      |\n");
	printf("|                                      |\n");
	printf("|                                      |\n");
	printf("|                                      |\n");
	printf("|           ��:�����ƶ�һ��            |\n");
	printf("|           ��:�����ƶ�һ��            |\n");
	printf("|           ��:�����ƶ�һ��            |\n");
	printf("|           ��:�����ƶ�һ��            |\n");
	printf("|         �ո�:������ת90��            |\n");
	printf("|         �س�:ȷ��                    |\n");
	printf("|                                      |\n");
	printf("|                                      |\n");
	printf("|           (�������������˵�)         |\n");
	printf("����������������������������������������");
	while(1)
	switch(getch()){
   		case 224:                    
     		switch(getch()){
        		case 75:
        			show_menu();
        	}
	}
}

void show_menu(){
	system("cls");
	printf("________________________________________\n");
	printf("|                                      |\n");
	printf("|            ��ս��Ϸģ��              |\n");
	printf("|              (������)                |\n");
	printf("|                                      |\n");
	printf("|                                      |\n");
	printf("|                     |��              |\n");
	printf("|              _______|___             |\n");
	printf("|             ��        ��             |\n");
	printf("|               ��������               |\n");
	printf("|                                      |\n");
	printf("|                                      |\n");
	printf("|                                      |\n");
	printf("|             ����ʼ��Ϸ               |\n");
	printf("|               ��Ϸ˵��               |\n");
	printf("|               ����˵��               |\n");
	printf("|               �˳���Ϸ               |\n");
	printf("|                                      |\n");
	printf("|                                      |\n");
	printf("|                                      |\n");
	printf("|    (�á���������ѡ�񲢰��س�ȷ��)    |\n");
	printf("����������������������������������������");
	switch(choose_menu()){
		case 0:start_game(0);break;
		case 1:game_des();break;
		case 2:butt_des();break;
		case 3:exit(0);
	}
}

void restart(){
	//��ͼ���� 
	for(int i=0;i<12;i++)
		for(int j=0;j<12;j++)
			map[j][i]=map_com[j][i]=-1;
			
	//ָ���ʼֵ�������ʼֵ����	
	flo=16,chx=1,chy=1;
	
	//���ջ 
	top=-1; 
	
	//��ʼ��Ϸ 
	show_menu();
}

void test(){
	com_rand();
	for(int i=0;i<12;i++)
		for(int j=0;j<12;j++)
			map[j][i]=map_com[j][i];
	test_com_fire(-1);
}
main(){
	test(); 
	//show_menu();
}
