class Relations::CreateService : public Relations::BaseService {
   CreateService(user:) {
    this->user = user
    this->contract_class = Relations::CreateContract
  }

   void call(relation, send_notifications: true) {
    in_context(send_notifications) {
      update_relation relation, {}
    }
  }
}
