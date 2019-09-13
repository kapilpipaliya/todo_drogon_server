namespace QueriesHelper {
   void retrieve_query() {
    @query = if ( params[:query_id].present?) {
               Query.where(project: @project).find(params[:query_id])
             else
               Query.new_default(name: '_',
                                 project: @project)
             }

    ::API::V3::UpdateQueryFromV3ParamsService
      .new(@query, current_user)
      .call(params)

    @query
  }
}
