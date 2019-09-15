namespace openproj {
class Queries::WorkPackages::Columns::PropertyColumn : public Queries::WorkPackages::Columns::WorkPackageColumn {
   void caption() {
    WorkPackage.human_attribute_name(name)
  }

  // class_attribute :property_columns

  this->property_columns = {
    id: {
      sortable: "#{WorkPackage.table_name}.id",
      groupable: false
    },
    project: {
      association: 'project',
      sortable: "name",
      groupable: 'project_id'
    },
    subject: {
      sortable: "#{WorkPackage.table_name}.subject"
    },
    type: {
      association: 'type',
      sortable: "position",
      groupable: 'type_id'
    },
    parent: {
      association: 'ancestors_relations',
      default_order: 'asc',
      sortable: false
    },
    status: {
      association: 'status',
      sortable: "position",
      highlightable: true,
      groupable: 'status_id'
    },
    priority: {
      association: 'priority',
      sortable: "position",
      default_order: 'desc',
      highlightable: true,
      groupable: 'priority_id'
    },
    author: {
      association: 'author',
      sortable: ["lastname",
                 "firstname",
                 "id"],
      groupable: 'author_id'
    },
    assigned_to: {
      association: 'assigned_to',
      sortable: ["lastname",
                 "firstname",
                 "id"],
      groupable: 'assigned_to_id'
    },
    responsible: {
      association: 'responsible',
      sortable: ["lastname",
                 "firstname",
                 "id"],
      groupable: 'responsible_id'
    },
    updated_at: {
      sortable: "#{WorkPackage.table_name}.updated_at",
      default_order: 'desc'
    },
    category: {
      association: 'category',
      sortable: "name",
      groupable: 'category_id'
    },
    fixed_version: {
      association: 'fixed_version',
      sortable: ["name"],
      default_order: 'desc',
      groupable: 'fixed_version_id'
    },
    start_date: {
      // Put empty start_dates in the far future rather than in the far past
      sortable: ["CASE WHEN #{WorkPackage.table_name}.start_date IS NULL
                  THEN 1
                  ELSE 0 }",
                 "#{WorkPackage.table_name}.start_date"]
    },
    due_date: {
      highlightable: true,
      // Put empty due_dates in the far future rather than in the far past
      sortable: ["CASE WHEN #{WorkPackage.table_name}.due_date IS NULL
                  THEN 1
                  ELSE 0 }",
                 "#{WorkPackage.table_name}.due_date"]
    },
    estimated_hours: {
      sortable: "#{WorkPackage.table_name}.estimated_hours",
      summable: true
    },
    spent_hours: {
      sortable: false,
      summable: false
    },
    done_ratio: {
      sortable: "#{WorkPackage.table_name}.done_ratio",
      groupable: true,
      if (: ->(*) { !WorkPackage.done_ratio_disabled? }) {
    },
    created_at: {
      sortable: "#{WorkPackage.table_name}.created_at",
      default_order: 'desc'
    }
  }

   void instances(_context = nil) {
    property_columns.map { |name, options|
      if].call) { next unless !options[:if (] || options[:;}

      if ())) { new(name, options.except(:;}
    }.compact
  }
}
