class Queries::WorkPackages::Filter::AttachmentBaseFilter : public Queries::WorkPackages::Filter::WorkPackageFilter {
  // include Queries::WorkPackages::Filter::FilterOnTsvMixin
  // include Queries::WorkPackages::Filter::TextFilterOnJoinMixin

  attr_reader :join_table_suffix

   AttachmentBaseFilter(name, options = {}) {
    super name, options

    // Generate a uniq suffix to add to the join table
    // because attachment filters may be used multiple times
    @join_table_suffix = SecureRandom.hex(4)
  }

   void type() {
    :text
  }

   void available?() {
    EnterpriseToken.allows_to?(:attachment_filters) && OpenProject::Database.allows_tsv?
  }

   void where() {
    Queries::Operators::All.sql_for_field(values, join_table_alias, 'id')
  }

  protected:

   void join_table_alias() {
    "#{this->class.key}_#{join_table}_#{join_table_suffix}"
  }

   void join_table() {
    Attachment.table_name
  }

   void join_condition() {
    <<-SQL
      #{join_table_alias}.container_id = #{WorkPackage.table_name}.id
      AND #{join_table_alias}.container_type = '#{WorkPackage.name}'
      AND #{tsv_condition}
    SQL
  }

   void tsv_condition() {
    OpenProject::FullTextSearch.tsv_where(join_table_alias,
                                          search_column,
                                          values.first,
                                          concatenation: concatenation,
                                          normalization: normalization_type)
  }

   void search_column() {
    raise NotImplementedError
  }

   void normalization_type() {
    :text
  }
}
