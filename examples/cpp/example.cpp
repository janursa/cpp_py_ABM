#include "example.h"
using namespace std;
shared_ptr<Cell> healingEnv::generate_agent(std::string agent_name){
		auto agent_obj = make_shared<Cell>(this->shared_from_this(),agent_name);
		this->agents.push_back(agent_obj);
		return agent_obj;
	}
shared_ptr<myPatch> healingEnv::generate_patch(){
		auto patch_obj = make_shared<myPatch>(this->shared_from_this());
		return patch_obj;
	}
void healingEnv::setup(){
	auto mesh = grid2(1.5, 1.5, 0.015, true);
	this->setup_domain(mesh);
	std::map<std::string,unsigned> settings = {{"cell",2000}};
	this->setup_agents(settings);
	this->damage();
	this->update();
	}
void healingEnv::damage(){
		for (auto &[index,patch]:this->patches){
			auto x = patch->coords[0];
			auto y = patch->coords[1];
			if ((x >= 0.25 and x <=1.25) and (y>=0.25 and y<=1.25)){
				patch->damage_center = true;
				patch->tissue = 0;
				if (patch->empty == false){
					patch->agent->disappear = true;
				}
					
			}
		}
	}
void healingEnv::update(){
		baseEnv<healingEnv,Cell,myPatch>::update();
		for (auto &agent: this->agents){
			agent->update();
		}
			
	}
void healingEnv::run(){
		for (auto &cell:this->agents){
			cell->step();
		}
		this->update();
		this->clock ++;
	}	
void Cell::step(){
	auto dest_patch = this->patch->empty_neighbor(true);
	this->order_move(nullptr,true,false);
	auto neighbor_cell_count = this->patch->find_neighbor_agents().size();
	if (this->patch->damage_center and this->clock >= 12){
		if (neighbor_cell_count <= 6){
			this->order_hatch(nullptr,false,true,false);
			this->clock = 0 ;
		}
	}
	if (this->patch->tissue < 100) {
		this->patch->tissue += 1;	
	}
		
	if (neighbor_cell_count >7){
		this->disappear = true;
	}
}