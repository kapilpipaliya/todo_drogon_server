namespace API {
  namespace V3 {
    class UpdateQueryFromV3ParamsService
       UpdateQueryFromV3ParamsService(query, user) {
        this->query = query
        this->current_user = user
      }

       void call(params, valid_subset: false) {
        parsed = ::API::V3::ParseQueryParamsService
                 .new
                 .call(params)

        if ( parsed.success?) {
          ::UpdateQueryFromParamsService
            .new(query, current_user)
            .call(parsed.result, valid_subset: valid_subset)
        else
          parsed
        }
      }

      attr_accessor :query,
                    :current_user
    }
  }
}
