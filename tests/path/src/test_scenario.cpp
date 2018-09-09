#include "test_scenario.h"

void TestScenario::initialize(int total_runs){

  od4.dataTrigger(opendlv::sim::scenario::Scenario::ID(), scenario_event);
  od4.dataTrigger(opendlv::sim::scenario::Frame::ID(), frame_event);

  std::ifstream file;
  std::vector<std::string> actions;

  file.open(base_path+std::to_string(scenario_id)+".path");

  if (file.is_open()){
    for(std::string line; std::getline(file, line); ){
      actions.push_back(line);
    }
  }else{
    std::cout << "SCENARIO NOT FOUND" << std::endl;
    return;
  }
  //basbase_run(0,this);
  for(int a = 0; a < actions.size(); a++){
    base_run.addAction(actions.at(a));
  }
  //base_run = btrun;
  //base_run = &btrun;

  /*base_run(0,this);
  for(int a = 0; a < actions.size(); a++){
    base_run.addAction(actions.at(a));
  }*/




  for(int r = 0; r < test_cases; r++){
    TestRun trun(r,this);
    for(int a = 0; a < actions.size(); a++){
      trun.addAction(actions.at(a));
    }
    runs.push_back(trun);
  }
  std::uniform_int_distribution<int> egen(0,actions.size()-1);
  error_gen = egen;
  std::cout << "--------------------STARTING--------------------" << std::endl;
  std::cout << "TESTCASES: " << test_cases << std::endl;
  std::cout << "RUNS:      " << total_runs << std::endl;
  std::cout << "ACTIONS:   " << actions.size() << std::endl;
  total_actions_run = actions.size();
  std::cout << "------------------------------------------------" << std::endl;
  std::cout << "--------------------BASETEST--------------------" << std::endl;
  generateErrors();
}

void TestScenario::scenarioEvent(opendlv::sim::scenario::Scenario scenario){
  switch(scenario.action()){
    case 2:{
      if(is_base_run){
        usleep(5000000); //give vdrift some headroom;
        std::thread (&TestRun::run,base_run).detach();
      }else{
        usleep(4000000); //give vdrift some headroom;
        std::cout << "TESTCASE   ["
                  << current_run << "/" << total_runs
                  << "]["
                  << current_test_case << "/" << test_cases
                  << "]["
                  << run_errors.at(current_test_case).type()
                  << "]["
                  << run_errors.at(current_test_case).position()
                  << "]["
                  << run_errors.at(current_test_case).value()
                  << "]" << std::endl;
        std::thread (&TestRun::run,runs.at(current_test_case)).detach();
      }


      break;
    }case 4 :{
      if(is_base_run) {
        --current_test_case;
        std::cout << "------------------BASETEST OK-------------------" << std::endl;
      }else{
        run_errors.at(current_test_case).deviation(getDeviation());
        runs.at(current_test_case).frames.clear();
        std::cout << "TESTRESULT ["
                  << current_run << "/" << total_runs
                  << "]["
                  << current_test_case << "/" << test_cases
                  << "]["
                  << run_errors.at(current_test_case).type()
                  << "]["
                  << run_errors.at(current_test_case).position()
                  << "]["
                  << run_errors.at(current_test_case).value()
                  << "]["
                  << std::to_string(run_errors.at(current_test_case).deviation())
                  << "]"
                  << std::endl;
      }

      if(++current_test_case == test_cases){
        std::cout << "------------------------------------------------" << std::endl;
        current_test_case = 0;
        ++current_run;

        std::ofstream out;
        std::string file = "/runs/"+test_method+".run";
        out.open(file, std::ios::app);
        if (out.is_open()){
          std::string str = std::to_string((current_run-1))+"\n";
          for(int i = 0; i< test_cases; i++){
            str += (std::to_string(run_errors.at(i).deviation())+",");
          }
          str += "\n";
          out << str;
        }
        out.close();
        //std::cout <<"-----------------------GENERATING ERRORS-------------------------" << std::endl;
        generateErrors();

      }


      if(current_run < total_runs){
        std::cout << "---------------------NEXT-----------------------" << std::endl;
        is_base_run = false;
        usleep(5000000);
        runs.at(current_test_case).start();
      }
      break;
    }
  }
}
void TestScenario::frameEvent(opendlv::sim::scenario::Frame frame){
  if(is_base_run)
    base_run.addFrame(std::move(frame));
  else
    runs.at(current_test_case).addFrame(std::move(frame));
}

/*int TestScenario::generateRandomFitest(int not_this){
  int arr[5];
  float best = -9999.0;
  int fittest = 0;
  for (int i = 0; i < 5; i++) {
    if(error_results[i] > best){
      int r = 0;
      do{
        //randomize();
        r = error_gen(mt);
      }while(r != not_this);
      arr[i] = r;
    }
  }
  for (int i = 0; i < 5; i++) {
    if(error_results[i] > best){
      best = error_results[i];
      fittest = i;
    }
  }
  return fittest;

}*/
TestError TestScenario::generateRandomFitest(int fittest){
  std::vector<TestError> tmp_errors;
  for (int i = 0; i < 5; i++) {
      int r = testcase_gen(mt);
      tmp_errors.push_back(run_errors.at(r));
  }
  auto fittest_it = std::max_element(tmp_errors.begin(), tmp_errors.end(), [](TestError a, TestError b){
      return a.deviation() < b.deviation();
  });
  return run_errors.at(std::distance(tmp_errors.begin(), fittest_it));

}
void TestScenario::generateErrors(){
  std::vector<TestError> new_run_errors;
  for(int e = 0; e < test_cases; e++){
    int error_type = error_gen(mt) % 2 +1;
    float error_value = 0.0;
    switch (error_type) {
      case 1:
        error_value = friction_error_gen(mt);
        break;
      case 2:
        error_value = steering_error_gen(mt);
        break;
    }
    TestError te(this, e, error_type, error_gen(mt) ,error_value);
    new_run_errors.push_back(te);
  }
  if(run_errors.size() > 0){
    if(test_method.compare("ga") == 0){
      auto fittest_it = std::max_element(run_errors.begin(), run_errors.end(), [](TestError a, TestError b){
          return a.deviation() < b.deviation();
      });
      int fittest_pos = std::distance(run_errors.begin(), fittest_it);
      TestError fittest = run_errors.at(fittest_pos);
      new_run_errors[0] = fittest;
      for (int i = 1; i < test_cases; ++i) {
          TestError r1 = generateRandomFitest(fittest_pos);
          TestError r2 = generateRandomFitest(fittest_pos);
          r1.crossover(r2);
          r1.mutate();
          new_run_errors[i] = r1;
      }
    }
  }
  run_errors = new_run_errors;

  /*

  int *new_errors = new int[test_cases];
  float *new_steering_errors = new float[test_cases];
  float *new_friction_errors = new float[test_cases];
  float *new_error_results = new float[test_cases];

  if(test_method.compare("ga") == 0 && !is_base_run){
    float best = -9999.0;
    int fittest = 0;
    for (int i = 0; i < test_cases; i++) {
      if(error_results[i] > best){
        best = error_results[i];
        fittest = i;
      }
    }
    new_errors[0] = errors[fittest];
    new_steering_errors[0] = steering_errors[fittest];
    new_friction_errors[0] = friction_errors[fittest];

    for (int i = 1; i < test_cases; i++) {
        int r1 = generateRandomFitest(fittest);
        int r2 = generateRandomFitest(fittest);
        // "CROSSOVER"
        int p = errors[r1];
        int s = steering_errors[r1];
        int f = friction_errors[r1];
        if(error_gen(mt) % 2 == 0) p = errors[r2];
        if(error_gen(mt) % 2 == 0) s = steering_errors[r2];
        if(error_gen(mt) % 2 == 0) f = friction_errors[r2];
        new_errors[i] = p;
        new_steering_errors[i] = s;
        new_friction_errors[i] = f;
        //mutate
        int m = error_gen(mt) % 3;
        switch (m) {
          case 0:
            new_errors[i] = error_gen(mt);
            break;
          case 1:
            new_steering_errors[i] = steering_error_gen(mt);
            break;
          case 2:
            new_friction_errors[i] = friction_error_gen(mt);
            break;
        }
    }
  }else{
    for(int e = 0; e < test_cases; e++){
      new_errors[e] = error_gen(mt);
      new_steering_errors[e] = steering_error_gen(mt);
      new_friction_errors[e] = friction_error_gen(mt);
    }
  }

  errors = new_errors;
  steering_errors = new_steering_errors;
  friction_errors = new_friction_errors;
  error_results = new_error_results;*/

}
float TestScenario::getDeviation(){
  float v = 0.0;
  float y_diff = 0.0;
  float x_diff = 0.0;

  if(!is_base_run){
    auto base_frames = base_run.frames;
    auto frames = runs.at(current_test_case).frames;
    int frame_count = base_frames.size();
    //calculcate diff between first first coordinates, for more reliable diviation
    /*x_diff = frames.at(0).x() - base_frames.at(0).x();
    y_diff = frames.at(0).y() - base_frames.at(0).y();
    for (int i=0; i < frame_count; i++){
      v += sqrt(
        pow((frames.at(i).y() - base_frames.at(i).y() - y_diff),2) +
        pow((frames.at(i).x() - base_frames.at(i).x() - x_diff),2)
      );
    }
    v = (v / frame_count);
    */
    VectorDTW dtw(frame_count,3);
    v = dtw.calculate(base_frames,frames);
  }

  return v;
}
bool TestScenario::hasTestCase(){
  return !is_base_run;
}

void TestScenario::insertError(int action){
  if(!hasTestCase()) return;
  run_errors.at(current_test_case).sendError(action);
}

double TestScenario::run(){
  base_run.start();
}


/*bool TestScenario::hasSteeringError(int test_case){
  return errors[current_test_case] == test_case;
}

float TestScenario::steeringError(){
  return steering_errors[current_test_case];
}

bool TestScenario::hasFrictionError(int test_case){
  return errors[current_test_case] == test_case;
}

float TestScenario::frictionError(){
  return friction_errors[current_test_case];
}




int TestScenario::mc(){
  int min = 1;
  int max = total_actions_run;
  return rand()%(max-min + 1) + min;
}

int TestScenario::ga(){
  return -1;

}*/
