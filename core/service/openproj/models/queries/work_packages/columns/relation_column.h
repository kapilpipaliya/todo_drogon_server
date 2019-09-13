class Queries::WorkPackages::Columns::RelationColumn : public Queries::WorkPackages::Columns::WorkPackageColumn {
  attr_accessor :type

   void granted_by_enterprise_token() {
    EnterpriseToken.allows_to?(:work_package_query_relation_columns)
  }

  private_class_method :granted_by_enterprise_token
}
