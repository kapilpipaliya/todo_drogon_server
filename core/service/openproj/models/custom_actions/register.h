namespace CustomActions::Register {
  class << self
     void action(action) {
      @actions ||= []

      @actions << action
    }

     void condition(condition) {
      @conditions ||= []

      @conditions << condition
    }

    attr_accessor :actions,
                  :conditions
  }
}
