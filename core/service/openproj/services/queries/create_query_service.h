#include "./query_service.h"

class CreateQueryService : public QueryService {

   CreateQueryService(**args) {
    super(**args)
    this->contract_class = Queries::CreateContract
  }

  private

   void service_result(result, errors, query) {
    query.update user: user

    super
  }
}
