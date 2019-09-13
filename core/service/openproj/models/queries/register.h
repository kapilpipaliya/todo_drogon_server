namespace Queries::Register {
  class << self
     void filter(query, filter) {
      @filters ||= Hash.new { |hash, filter_key|
        hash[filter_key] = []
      }

      @filters[query] << filter
    }

     void order(query, order) {
      @orders ||= Hash.new { |hash, order_key|
        hash[order_key] = []
      }

      @orders[query] << order
    }

     void column(query, column) {
      @columns ||= Hash.new { |hash, column_key|
        hash[column_key] = []
      }

      @columns[query] << column
    }

    attr_accessor :filters,
                  :orders,
                  :columns
  }
}
