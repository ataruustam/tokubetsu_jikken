#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <random>
#include <ctime>
#define N 10000

//define size_xy (main) and flight length mu (run_manager::FlightLength())

//std::mt19937 mt((int)time(0));
std::mt19937 mt(1);

//座標
class coordinate{
public:
	coordinate(){;}
	void set_coordinate(double xin,double yin, double zin)
	{
		x=xin;
		y=yin;
		z=zin;
	}
	double get_x(){return x;}
	double get_y(){return y;}
	double get_z(){return z;}
private:
	double x,y,z;
};


//イベントの制御、各種条件
class run_manager{
public:
	run_manager(double size_xy,double size_z){
		xy=size_xy;
		z=size_z;
	}

	//ガンマ線の発射位置を決める
	void SetStartPosition();
	//ガンマ線の発射位置を得る
	coordinate GetStartPosition(){return StartPosition;}
	//ガンマ線の方向を決める
	void SetDirection();
	//ガンマ線の方向を得る
	coordinate GetDirection(){return Direction;}
	//ガンマ線の飛距離を決める
	double FlightLength();
	//Fe箔の外に出たことを判定する
	bool go_out(coordinate end);



private:
	//鉄箔のサイズ、厚みを保持
	double xy,z;
	//発射位置を保持するクラス
	coordinate StartPosition;
	//発射方向を保持するクラス
	coordinate Direction;
};

void run_manager::SetStartPosition(){
	//std::mt19937 mt((int)time(0));
	std::uniform_real_distribution<double> XYposition(0,xy);
	std::uniform_real_distribution<double> Zposition(0,z);
	//prepare for coordinate
	StartPosition.set_coordinate(XYposition(mt)-xy/2.,XYposition(mt)-xy/2.,Zposition(mt)-z/2.);
}

void run_manager::SetDirection(){
	//std::mt19937 mt((int)time(0));
	std::uniform_real_distribution<double> Theta(0,M_PI);
	std::uniform_real_distribution<double> Phi(0,2*M_PI);
	//prepare for coordinate
	double theta=Theta(mt);
	double phi=Phi(mt);
	Direction.set_coordinate(sin(theta)*cos(phi), sin(theta)*sin(phi), cos(theta));
	//Direction.set_coordinate(cos(phi), sin(phi), 0);
	//std::cout << sqrt(Direction.get_x()*Direction.get_x()+Direction.get_y()*Direction.get_y()+Direction.get_z()*Direction.get_z()) << std::endl;
}


bool run_manager::go_out(coordinate end){
	if(fabs(end.get_x())>xy/2. || fabs(end.get_y())>xy/2. || fabs(end.get_z())>z/2. ) return true;
	else return false;
}

double run_manager::FlightLength(){
	//flight length
	double mu=0.02;
	std::uniform_real_distribution<double> y(0,1);
	double x=-log(1.-y(mt))*mu;
	//std::cout << x << std::endl;
	return x;
}

class run_event{
public:
	run_event(run_manager* inrun)
	:run(inrun)
	{;}
	bool GetResult();
private:
	run_manager* run;
};

bool run_event::GetResult(){
	double x,y,z;
	coordinate event;
	run->SetStartPosition();
	run->SetDirection();
	double l=run->FlightLength();
	x=run->GetStartPosition().get_x()+l*run->GetDirection().get_x();
	y=run->GetStartPosition().get_y()+l*run->GetDirection().get_y();
	z=run->GetStartPosition().get_z()+l*run->GetDirection().get_z();
	event.set_coordinate(x, y, z);
	//std::cout << "(" << event.get_x() << "," << event.get_y() << "," << event.get_z() << ")" << std::endl;

	if(run->go_out(event)) return true;
	else return false;

	//return event;
}


int main(){
	//size of Fe film
	double size_xy,size_z;
	size_xy=4.6;
	//size_z=0.04;

	for(int j=1;j<100;++j){
		int sum=0;
		size_z=0.001*j;
		run_manager run(size_xy,size_z);
		for(int i=0;i<j*N;++i){
			run_event event(&run);
			//std::cout << event.GetResult().get_x() << std::endl;
			if(event.GetResult()) sum++;
		}
		//std::cout << size_z << " " << (double)sum/N << std::endl;
		std::cout << sum*100./(j*N) << std::endl;
	}

	//test SetStartPosition
	/*
	run->SetStartPosition();
	std::cout << "position: " << run->GetStartPosition().get_x() << "," <<  run->GetStartPosition().get_y() << "," << run->GetStartPosition().get_z() << std::endl;
	*/

	//test SetDirection
	/*
	run->SetDirection();
	double dir_x,dir_y,dir_z;
	dir_x=run->GetDirection().get_x();
	dir_y=run->GetDirection().get_y();
	dir_z=run->GetDirection().get_z();
	std::cout << "direction: " << dir_x << "," << dir_y << "," << dir_z << std::endl;
	std::cout << "proof: " << sqrt(dir_x*dir_x + dir_y*dir_y + dir_z*dir_z) << std::endl;
	*/

	//test go_out
	/*
	coordinate dummy;
	dummy.set_coordinate(2.0, 2.0, 0.0);
	if(run->go_out(dummy)) std::cout << "true" << std::endl;
	else std::cout << "false" << std::endl;
	*/

	return 0;
}
