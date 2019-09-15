#pragma once
#include "application_job.h"
//#include "rake"

//
// Invoke a rake task while safely loading the tasks only once
// to ensure they are neither loaded nor executed twice.
namespace openproj {
class RakeJob : public ApplicationJob {
public:

//  attr_reader :task_name

//   RakeJob(task_name) {
//    this->task_name = task_name
//  }

   void perform() {
//    Rails.logger.info { "Invoking Rake task #{task_name}." }
//    invoke
  }

  protected:

   void invoke() {
//    load_tasks!
//    task.invoke
  }

  private:

  //
  // Load tasks if there are none. This should only be run once in an environment
   void load_tasks() {
//    raise unless tasks_loaded?
//  rescue StandardError
//    OpenProject::Application.load_rake_tasks
  }

  //
  // Reference to the task name.
  // Will raise NameError or NoMethodError depending on what of rake is (not) loaded
   void task() {
//    Rake::Task[task_name]
  }

  //
  // Returns whether any task is loaded
  // Will raise NameError or NoMethodError depending on what of rake is (not) loaded
   bool tasks_loaded() {
//    !Rake::Task.tasks.empty?
  }
};
}
