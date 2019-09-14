namespace QueriesHelper {
   void retrieve_query() {
    this->query = if ( params[:query_id].present?) {
               Query.where(project: this->project).find(params[:query_id])
             else
               Query.new_default(name: '_',
                                 project: this->project)
             }

    ::API::V3::UpdateQueryFromV3ParamsService
      .new(this->query, current_user)
      .call(params)

    this->query
  }
}
