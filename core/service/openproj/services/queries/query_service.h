namespace openproject {
class QueryService
  // include Concerns::Contracted

  attr_reader :user

   QueryService(user:) {
    this->user = user
  }

   void call(query) {
    result, errors = validate_and_save(query, user)

    service_result result, errors, query
  }

  private:

   void service_result(result, errors, query) {
    ServiceResult.new success: result, errors: errors, result: query
  }
}
