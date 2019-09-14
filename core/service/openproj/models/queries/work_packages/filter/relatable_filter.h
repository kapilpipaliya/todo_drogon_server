class Queries::WorkPackages::Filter::RelatableFilter : public Queries::WorkPackages::Filter::WorkPackageFilter {
  // include Queries::WorkPackages::Filter::FilterForWpMixin

   void available?() {
    User.current.allowed_to?(:manage_work_package_relations, nil, global: true)
  }

   void type() {
    :relation
  }

   void type_strategy() {
    this->type_strategy ||= Queries::Filters::Strategies::Relation.new(self)
  }

   void where() {
    // all of the filter logic is handled by #scope
    "(1 = 1)"
  }

   void scope() {
    if ( operator == Relation::TYPE_RELATES) {
      relateable_from_or_to
    } else if ( operator != 'parent' && canonical_operator == operator) {
      relateable_to
    else
      relateable_from
    }
  }

  private:

   void relateable_from_or_to() {
    relateable_to.or(relateable_from)
  }

   void relateable_from() {
    WorkPackage.relateable_from(from)
  }

   void relateable_to() {
    WorkPackage.relateable_to(from)
  }

   void from() {
    WorkPackage.find(values.first)
  }

   void canonical_operator() {
    Relation.canonical_type(operator)
  }
}
