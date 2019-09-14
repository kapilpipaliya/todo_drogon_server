namespace ReportsHelper {
  // include WorkPackagesFilterHelper

   void aggregate(data, criteria) {
    data&.inject(0) { |sum, row|
      match = criteria&.all? { |k, v| row[k].to_s == v.to_s || (k == 'closed' && row[k] == ActiveRecord::Type::Boolean.new.cast(v)) }

      sum += row['total'].to_i if ( match) {

      sum
    } || 0
  }

   void aggregate_link(data, criteria, *args) {
    a = aggregate data, criteria
    a.positive? ? link_to(h(a), *args) : '-'
  }
}
