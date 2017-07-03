#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>

void gotoxy(int x,int y);//鼠标光标移动 
int choose_menu();//开始界面选择菜单 
int choose_boat();//选择移动战舰 
void butt_des();//按键说明界面 
void show_menu();//开始菜单界面 
void start_game(int t);//开始游戏界面 
void restart();//重新开始游戏 
void move(int type,int a,int b);//玩家战舰布局 
void game_des();//游戏说明界面 
void com_rand();//电脑战舰布局 
void open_fire();//布局完成后开炮界面 
void com_fire(int xy);//电脑开炮
void fire();//玩家开炮 
void push(int item1,int item2);//插入坐标 
void pop();//删除坐标 
int search(int n,int direction);//已有坐标向外扩展
void write_data(int xy,int i); //向文件中记录打炮坐标及是否击中 

/*
测试说明
0.在主函数注释show_menu()函数
1.在主函数中调用test()
*/
void test();//专门用来测试电脑随机开炮功能 
void test_com_fire(int i);
void test_fire();

//存放玩家信息的地图 
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


//存放电脑信息的地图				  
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
				      

//战舰选择界面小箭头的初始y值 
int flo=16;
//记录玩家开炮的落点 
int chx=1,chy=1;

//战舰信息 
typedef struct boat{
	int length;//长度 
	int state;//横竖 
	int x;//x坐标 
	int y;//y坐标 
}Boat;
Boat boat[5]={{2,0,0,0},{3,0,0,0},{3,0,0,0},{4,0,0,0},{5,0,0,0}};

//栈的定义 
typedef struct stack{
	int coord;
	int next;
}Stack;
//top为栈顶坐标 
int top=-1;
Stack boat_attacked[20];

void write_data(int xy,int i){
	FILE *fp;
	fp=fopen("boat.txt","a+");//以追加形式写入 
	fprintf(fp,"%d,%d",xy/10+1,xy%10+1);
	switch(i){
		case -1:fprintf(fp,"--未击中\n");break;
		case 0:fprintf(fp,"--击中\n");break;
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
		case 0://上 
			if(n%10==0)
				return n;
			else
				return n-1;
			break;
		case 1://下 
			if(n%10==9)
				return n;
			else
				return n+1;
			break;
		case 2://左 
			if(n/10==0)
				return n;
			else
				return n-10;
			break;
		case 3://右 
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
		printf("%d,%d--未击中\n",xy/10+1,xy%10+1);
		map[xy/10+1][xy%10+1]=1;
		num++;
		pop();
		test_fire();
		test_com_fire(-1);
	}
	if(map[xy/10+1][xy%10+1]==0){
		printf("%d,%d--击中",xy/10+1,xy%10+1);
		map[xy/10+1][xy%10+1]=1;
		num++;
		next=-1;
		j=k=boat_attacked[top].coord;
		printf("初始k为%d,%d next=%d\n",k/10+1,k%10+1,next);
	while(next<4){
		next++;
		j=k;
		while(map[search(j,next)/10+1][search(j,next)%10+1]==0){
			map[search(j,next)/10+1][search(j,next)%10+1]=1;
			printf("%d,%d--击中 next=%d",search(j,next)/10+1,search(j,next)%10+1,next);
			push(search(j,next),next);
			j=boat_attacked[top].coord;
			if(map[search(j,next)/10+1][search(j,next)%10+1]==-1){
				printf("%d,%d--未击中+ next=%d\n",search(j,next)/10+1,search(j,next)%10+1,next);
				map[search(j,next)/10+1][search(j,next)%10+1]=1;
				num++;
				test_fire();
		}
		}
		if(map[search(k,next)/10+1][search(k,next)%10+1]==-1){
			printf("%d,%d--未击中= next=%d\n",search(k,next)/10+1,search(k,next)%10+1,next);
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
	//num为开炮次数 
	static int num=0;
	int i,j,k,next,n=0;
	//当电脑全部击中后 
	if(top==16){
		system("cls"); 
		printf("you lose\n");
		printf("按任意键继续");
		getch();
		//可以选择再玩一局或退出 
		printf("输入r重玩或q退出");
		switch(getch()){
			case 'r':
				restart();
				break;
			case 'q':exit(0);
			default:exit(0);
		} 
	}
	//当传入参数为-1时则为随机开炮 
	//随机开炮时遵守前50炮不打相邻坐标的原则  增加击中概率 
	if(xy==-1){
		xy=rand()%100;
		if(num<50)
		do{
			xy=rand()%100;
		}
		while((xy/10%2+xy)%2!=0);
	}
	//当开炮打到已打过的坐标时则继续开炮 
	if(map[xy/10+1][xy%10+1]==1)
		com_fire(-1);
		//将此坐标入栈 
	push(xy,-1);
	//若未打中 先在界面中显示 在写入文件 再在地图中记录 将坐标出栈 
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
	//若打中 
	if(map[xy/10+1][xy%10+1]==0){
		gotoxy(xy/10+16,xy%10+1);
		printf("+");
		write_data(xy,0);
		num++;
		map[xy/10+1][xy%10+1]=1;
		next=-1;
		//k存下初始击中坐标  j作为探索坐标
		j=k=boat_attacked[top].coord;
		//探索击中坐标的四周 
	while(next<4){
		next++;
		j=k;
		//当击中坐标的某一方向仍被击中  则深度遍历该方向  直到击中到空坐标或墙或已击过的坐标  并将击中的船体坐标入栈 
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
	flag=1;//flag作用为判断是否结束玩家开炮 
	gotoxy(chx,chy);
	while(flag)
	switch(getch()){
		case 13:
			int win;
			win=0;
			//若玩家击中 
			if(map_com[chx][chy]==0){
					gotoxy(chx,chy);
					printf("+");
					//电脑地图上记下被击中的坐标
					map_com[chx][chy]=2;
					//遍历整个地图判断是否玩家已获胜 
					for(int x=1;x<11;x++)
						for(int y=1;y<11;y++)
							if(map_com[x][y]==2)
								win++;
							if(win==17){
							system("cls");
							printf("you win\n");
							getch();
							printf("输入r重玩或q退出");
							switch(getch()){
								case 'r':
									restart();
									break;
								case 'q':exit(0);
								default:exit(0);
							}
						}
						//继续开炮 
					fire();
				}
				//若未击中 
			if(map_com[chx][chy]==-1){
					gotoxy(chx,chy);
					printf("-");
					map_com[chx][chy]=1;
					if(top==-1)//当玩家是第一炮时则电脑随机开炮 
					com_fire(-1);
					//当玩家是在上轮  电脑击中再未击中的情况下开炮的  则结束此次开炮让电脑根据击中情况开炮而不是随机 
					if(boat_attacked[top].next!=4){
					flag=0;
					break;
				}
				//当上轮电脑是随机开炮的  则再次让电脑随机开炮 
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
	//flag为布置完的船的数量  当全部布置完则退出布置 
	while(flag<5){
		num=rand()%200+100;//生成一个100-299的随机数  百位代表横竖  十位代表船头横坐标  个位代表船头纵坐标 
		if(num/100==1){
			if(num/10%10>10-boat[flag].length)//若船头加上船长度越过边界  则重新生成 
				continue;
			for(i=0;i<boat[flag].length;i++)//若船重叠  退出循环 
				if(map_com[num/10%10+1+i][num%10+1]==0)
					break;
				if(i<boat[flag].length)//若上面循环为中途退出的  则重新生成 
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

//光标移动函数 
void gotoxy(int x,int y)
{
	HANDLE hout;
	COORD coord;
	coord.X=x;
	coord.Y=y;
	hout=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hout,coord);
}

//move函数是移动战舰的关键函数 
//type为传入战舰的型号  a为船头x坐标 b为船头y坐标 
void move(int type,int a,int b){
	int x=a,y=b;
	int i=0;
	int flag=0,flag2=0;//flag用来标记当旋转时是否会撞墙或撞到战舰  flag2用来标记移动时是否会撞墙或撞到战舰 
	while(1)
	switch(getch()){
		
		//当按回车时 
		case 13:start_game(1);break;
		
		//当按空格时 
		case 32:
			//如果船之前为横则变为竖  如果为竖则变为横 
			boat[type].state=boat[type].state==0;
			flag=0;
			if(boat[type].state==1){
				for(i=1;i<boat[type].length;i++)
				//当船体有一部分撞到墙或战舰时 立下flag并退出循环 
					if(y>11-boat[type].length||map[x][y+i]==0){
						gotoxy(0,16);
						flag=6;
						break;
					}
					//当收flag时 旋转失效  并退出此次旋转 
					if(flag==6){
						boat[type].state=boat[type].state==0;
						break;
					} 
				for(i=1;i<boat[type].length;i++){
					//清除旋转前的船体显示并在地图上设为空 
			    	gotoxy(x+i,y);
			    	printf(" ");
			    	map[x+i][y]=-1;
			    	//显示旋转后的船体 
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
			
		//当按上下左右时 
		case 224:                    
			switch(getch()){
				//上 
        		case 72:
        			flag2=0;
			        if(boat[type].state==0){
			        	for(i=0;i<boat[type].length;i++)
			        	//如果船撞到其他船 则立下flag2并退出循环 
							if(map[x+i][y-1<1?10:y-1]==0){
								flag2=6;
								break;
							}
							//收flag2时 退出此次移动操作  即不移动 
							if(flag2==6) break;
							//清除移动前的船体 
			        	for(i=0;i<boat[type].length;i++){
			        		gotoxy(x+i,y);
			        		printf(" ");
			        		map[x+i][y]=-1;
						}
			    		if(y==1) y=11;//若遇到边界  则穿过边界到下面 
						y--;
						//显示移动之后的船体 
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
			    //下 
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
				//左 
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
			    //右 
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

//传入参数t是当初次游戏时战舰显示为默认布局，而当移动时仍然使用此界面，但战舰不需要再返回为初次布局时的位置，故跳过战舰初始位置布置
//t==0时战舰为默认布局  t!=1时继承上次布局 
void start_game(int t){
	int i,x,y;
	if(t==0){
		//战舰初始布局  
	boat[0].x=1,boat[0].y=1;//船头设置 
	for(i=1;i<3;i++) map[i][1]=0;//船在地图占位 
	
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
	printf("\n\n选中战舰回车后移动，再按回车继续\n\n");
	printf("  →护卫舰(占2格)\n");
	printf("    驱逐舰(占3格)\n");
	printf("    潜艇舰(占3格)\n");
	printf("    战列舰(占4格)\n");
	printf("    航空母舰(占5格)\n");
	printf("    确认放置完毕\n");
}
//根据地图显示战舰布局 
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
		//打印map  gotoxy(0,40);for(i=0;i<12;i++) for(int j=0;j<12;j++) printf("%2d%c",map_com[j][i],j==11?'\n':' ');gotoxy(0,25);for(i=0;i<12;i++) for(int j=0;j<12;j++) printf("%2d%c",map[j][i],j==11?'\n':' ');
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
			        if(y==16)//指针到第一个时再按上则跳到最后一个 
			        y=22;
			        gotoxy(2,y-=1);
			        printf("→");
			        flo=y;
			        break;
		        case 80:
		        	gotoxy(2,y);
			        printf(" ");
			        if(y==21)//指针到最后一个时再按下则跳到第一个 
		        	y=15;
		        	gotoxy(2,y+=1);
		            printf("→");
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
			        printf("→");
			        break;
		        case 80:
		        	gotoxy(14,y);
			        printf(" ");
			        if(y==16)
		        	y=12;
		        	gotoxy(14,y+=1);
		            printf("→");
		            break;
		     }
			 break;   
	}
}

void open_fire(){
	int i;
	system("cls");
	
	//显示玩家地图 (暗)
	printf("------------\n");
	printf("|*         |\n");
	for(i=0;i<9;i++)
	printf("|          |\n");
	printf("------------\n");
	printf("\n按回车后确认开炮");
	
	//显示电脑地图 (暗)
	gotoxy(15,0);
	printf("------------");
	for(i=0;i<10;i++){
	gotoxy(15,1+i);
	printf("|          |");
} 
	gotoxy(15,11);
	printf("------------");
	
	//显示玩家布置后的地图 (明)
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
/*  输出电脑随机后的战舰布局 
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
	printf("|            海战游戏模拟              |\n");
	printf("|              (单机版)                |\n");
	printf("|                                      |\n");
	printf("|                                      |\n");
	printf("|                     |＞              |\n");
	printf("|              _______|___             |\n");
	printf("|             ＼        ／             |\n");
	printf("|               ￣￣￣￣               |\n");
	printf("|                                      |\n");
	printf("|                                      |\n");
	printf("|     游戏说明：玩家和电脑各自在两块   |\n");
	printf("|     10 *10的棋盘中放置战舰，每方五   |\n");
	printf("|     艘,且对对方隐形,放好后不能移动   |\n");
	printf("|     每艘船可横竖任意放置但不能接触   |\n");
	printf("|     更不能重叠，双方轮流轰炸对方的   |\n");
	printf("|     敌舰，每次的轰炸结果均显示出来   |\n");
	printf("|     若击中则可继续攻击，未击中则轮   |\n");
	printf("|     到对方，要击沉一艘战舰则要所有   |\n");
	printf("|     击中所有格子，游戏目标是在对手   |\n");
	printf("|     之前将对方战舰全部击沉。         |\n");
	printf("|                                      |\n");
	printf("|           (按←键返回主菜单)         |\n");
	printf("￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣");
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
	printf("|            海战游戏模拟              |\n");
	printf("|              (单机版)                |\n");
	printf("|                                      |\n");
	printf("|                                      |\n");
	printf("|                     |＞              |\n");
	printf("|              _______|___             |\n");
	printf("|             ＼        ／             |\n");
	printf("|               ￣￣￣￣               |\n");
	printf("|                                      |\n");
	printf("|                                      |\n");
	printf("|                                      |\n");
	printf("|                                      |\n");
	printf("|           ↑:向上移动一格            |\n");
	printf("|           ↓:向下移动一格            |\n");
	printf("|           ←:向左移动一格            |\n");
	printf("|           →:向右移动一格            |\n");
	printf("|         空格:船体旋转90°            |\n");
	printf("|         回车:确认                    |\n");
	printf("|                                      |\n");
	printf("|                                      |\n");
	printf("|           (按←键返回主菜单)         |\n");
	printf("￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣");
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
	printf("|            海战游戏模拟              |\n");
	printf("|              (单机版)                |\n");
	printf("|                                      |\n");
	printf("|                                      |\n");
	printf("|                     |＞              |\n");
	printf("|              _______|___             |\n");
	printf("|             ＼        ／             |\n");
	printf("|               ￣￣￣￣               |\n");
	printf("|                                      |\n");
	printf("|                                      |\n");
	printf("|                                      |\n");
	printf("|             →开始游戏               |\n");
	printf("|               游戏说明               |\n");
	printf("|               按键说明               |\n");
	printf("|               退出游戏               |\n");
	printf("|                                      |\n");
	printf("|                                      |\n");
	printf("|                                      |\n");
	printf("|    (用↑↓键进行选择并按回车确认)    |\n");
	printf("￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣");
	switch(choose_menu()){
		case 0:start_game(0);break;
		case 1:game_des();break;
		case 2:butt_des();break;
		case 3:exit(0);
	}
}

void restart(){
	//地图重置 
	for(int i=0;i<12;i++)
		for(int j=0;j<12;j++)
			map[j][i]=map_com[j][i]=-1;
			
	//指针初始值及坐标初始值重置	
	flo=16,chx=1,chy=1;
	
	//清空栈 
	top=-1; 
	
	//开始游戏 
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
