namespace openproj {
class Queries::WorkPackages::Columns::ManualSortingColumn : public Queries::WorkPackages::Columns::WorkPackageColumn {
  // include ::Queries::WorkPackages::Common::ManualSorting

   ManualSortingColumn() {
    super :manual_sorting,
          default_order: 'asc',
          sortable: "#{OrderedWorkPackage.table_name}.position NULLS LAST, #{WorkPackage.table_name}.id"
  }

   void sortable_join_statement(query) {
    ordered_work_packages_join(query)
  }
}
