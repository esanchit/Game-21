/***************************************************************
** Program filename: Assignment 3 code
** Author: Sanchit Chopra
** Date: 01/03/2019
** Description: This program is a game called Twenty one similar to blackjack.In this player will be ask to play with dealer and cards will be drawn for both of them and at the        end, whosoever's sum is close to 21 will win.
** Input: rand() function is used for drawing cards for player and dealer.Two diiferent functions are also creadted one for player and other for dealer.    
** Output:In this part of the program we will get the winner of the game along with the amount of the winner will have after winning.       
***************************************************************/
#include<iostream>
#include<cmath>
#include<climits>
#include<cstdlib>



int startingmoney[5] = {};   // This is an array which will be saving the money that the player is starting with.
int betmoney[5] = {};       // This array will save the money that the player is betting. 
int deal[5] = {};	   // This array saves the total points of the each player which have to be compared with the dealer for each of them.  
	
/*************************************************************
** Program filename: Player game
** Author: Sanchit Chopra
** Date: 01/03/2019
** Description:This is function made for player game.In this player will asked to bet some amount anthe cards will be drawn, if the sum goes greater than 21, no more cards will be   drawn and the player will lose.Else, the points of the player will be compared to the dealer and the winner will be deaclared.      
** Input: rand() function is used to draw cards for the player.
**Output: Player's total points after completing their turn. 
************************************************************/
int player_turn(int n){
	int i = 0;
	int max_loop = 0;
	for(i = 1;i <= n;i++){
		if(startingmoney[i] == 0){
			std::cout<<"Player "<< i <<", has no money left in the account!!!"<<std::endl;   // This will be printed when the player has no money left. 
			std::cout<<"Therefore, Player "<< i <<", can't play more."<<std::endl;
			continue;
		}
		std::cout<<"Player "<< i <<", how much do you bet you can bet the dealer?"<<std::endl;   // Asking for the amount the player want to bet.
		std::cin>> betmoney[i];

		while(betmoney[i] > startingmoney[i]){
			std::cout<<"Your betting money is larger than your starting money!!!"<<std::endl;   // When the betting money gets higher than the starting money.
			std::cout<<"Enter a betting money again: "<<std::endl;
			std::cin>> betmoney[i];
		}
		int sum = 0;
		int play = 1;
		int num_p = 0;
		int loop = 0;
		int flag = 0;
	
		while(play == 1){
			srand(time(NULL));
			num_p = rand() % 11 + 1;
			std::cout<<"Player "<< i <<", you got "<< num_p <<".Do you want to go again,Enter 1 for yes and 0 for no. "<<std::endl; // One Card is drawn, asking for another one.
			std::cin>>play; 
			sum = sum + num_p;
	
			if(sum > 21){
				std::cout<<"You total points are: "<< sum <<std::endl;    //Telling the player that the sum exceeds 21 and the player lost. 
				std::cout<<"You lost from dealer because of the exceeding sum by 21!!!"<<std::endl;
				flag = 1;
				break;
			}
			else{
				loop++; // calculating how much times the loop had be executed. 
			}
			if (loop > max_loop){
				max_loop = loop;
			}
		}
		if (flag == 1){
			continue;
		}
		if (sum <= 21){
			deal[i] = sum;
		}
		else{
			deal[i] = 0;  // if the sum is greater than 21 then the deal[i] used for saving sum will save zero for that player.
		}
		std::cout<<"Your total points are: "<< sum <<"\n\n";  //Telling total points for the player.
	}
	return max_loop; 
}

/******************************************************
**  Program filename: Dealer game
**  Author: Sanchit Chopra
**  Date: 01/03/2019
**  Description: This function wll be execcuted after all the players are finished with their turn and then the dealer will play and the cards will be drawn if the dealer sum gets      exceeded by 21 then the dealer lost. Else, the dealer points will be compared with player's point and the winner will be declared
**  Input: rand() function is used to draw the cards for dealer.
**  Output: Total points for the dealer and comparing and telling who win and lose.
******************************************************/ 
void dealer_turn(int max_loop,int n){
	int num_d = 0;
	int dplay = 0;
	int sum_d = 0;
	int flag = 0;
	int i = 0;
	while(dplay <  max_loop){
		srand(time(NULL));
		num_d = rand() % 11 + 1;
		std::cout<<"The dealer got: "<< num_d <<std::endl; // Drawing cards for dealer that is one time less than the max time the cards had been drawn.  
		sum_d = sum_d + num_d;
		dplay++;
		if(sum_d > 21){
			std::cout<<"Points of dealer exceeded 21."<<"\n\n";
			for(i = 1;i <= n;i++){
				if(deal[i] == 0){
					std::cout<<"Player "<< i <<" and dealer both exceeded. So, both lost "<<std::endl;     // if both exceeded by 21 then both lost.
					startingmoney[i] = startingmoney[i] - betmoney[i];
					std::cout<<"So, Player "<< i <<", current money is: "<< startingmoney[i] <<std::endl; 
			
				}
				else{
				std::cout<<"Therefore,Player "<< i <<", won and dealer got bust."<<std::endl;  // if just the dealer exceeded by 21.
				startingmoney[i] = startingmoney[i] + betmoney[i];
				std::cout<<"So,Player "<< i <<", current money is: "<< startingmoney[i] <<std::endl;
				}
			}
			return;
		}
	}

	std::cout<<"Dealer's total point are: "<< sum_d <<"\n\n";
	
	for(i = 1;i <= n;i++){
		if(deal[i] > sum_d){
		std::cout<<"Dealer got bust!!!"<<"Player "<< i <<", won."<<std::endl;  // If Player won this whole will execute. 
		startingmoney[i] = betmoney[i] + startingmoney[i];
		std::cout<<"So,Player "<< i <<", current money is : "<< startingmoney[i] <<"\n\n";
		}
		else if(deal[i] == sum_d){
			std::cout<<"Player "<< i <<" and dealer points have same points. So, tie."<<std::endl; // If both get the same points. 
			std::cout<<"Player "<< i <<", has same amount left in acoount: "<< startingmoney[i] <<"\n\n";
		} 
		else{
			std::cout<<"Player "<< i <<" ,got bust! Dealer won."<<std::endl;  // If the dealer won this will execute.
			startingmoney[i] = startingmoney[i] - betmoney[i];
			std::cout<<"So,Player "<< i <<", current money is: "<< startingmoney[i] <<"\n\n";
		}
	}
}
/***************************************************************
** Program filename: Main function
** Author: Sanchit Chopra
** Date: 03/01/2019
** Description: This is the main function which is executing.
** Input: We are providing player function and dealer function to this main function.
** Output: Who wins or lose and what amount they have at that time in their account.  
****************************************************************/
int main() {
	int n = 0;
	int play = 1;
	int i =  0;
	std::cout<<"Welcome to Twenty one game..."<<std::endl;
	std::cout<<"In this game players will be asked to have some starting money and then bet with dealer.All the players will play in the starting and cards will be drawn.After they are finished  the dealer will play.Finally each player scores will be compared with dealer and whosoever get close to 21 will win."<<std::endl; //Few instructions for the game.
	std::cout<<"Ready to play this game...Let start. "<<"\n\n"; 
	std::cout<<"How many players are playing this game , total can be 4."<<std::endl;  //Asking how many players are playing. 
	std::cin>>n;
	for(i = 1;i <= n;i++){
		std::cout<<"Player "<< i <<", how much are you starting money do you want int your account? "<<std::endl; //Asking for money the player want in their account in satrting.
		std::cin>>startingmoney[i];
	}
	while(play == 1){
		int max_loop = player_turn(n);
		dealer_turn(max_loop,n);

		std::cout<<"Do you want to play again or cash out,Enter 1 for playing again or 0 for cash out."<<std::endl;  // asking if they want to play again or cash out.
		std::cin>> play;	

		if(play == 0){
			for(i = 1;i <= n;i++){
				std::cout<<"Player "<< i <<" , is left with: "<<startingmoney[i] <<std::endl;   //Telling the ending amount in the account after they decided to cash out.
			}
			return 0;
		}
		
		int nomoney_flag = 0;

		for(i = 1;i <= n;i++){
			if(startingmoney[i] != 0){
			}
			else{
				nomoney_flag++;
			}
		} 
		if(nomoney_flag == n){
			std::cout<<"All players ran out of money...exiting game!!!"<<std::endl;  // Exiting game if all players ran out of money.
			return 0;
		}
	}	
	return 0;
}

