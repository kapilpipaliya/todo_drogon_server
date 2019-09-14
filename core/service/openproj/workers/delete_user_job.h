namespace openproject {
class DeleteUserJob : public ApplicationJob {
   DeleteUserJob(user_id) {
    this->user_id = user_id
  }

   void perform() {
    user.destroy
  }

  private:

   void user() {
    this->user ||= User.find this->user_id
  }
}
