class DeleteUserJob : public ApplicationJob {
   DeleteUserJob(user_id) {
    @user_id = user_id
  }

   void perform() {
    user.destroy
  }

  private:

   void user() {
    @user ||= User.find @user_id
  }
}
