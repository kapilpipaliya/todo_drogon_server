namespace CustomActions::Actions::Strategies::Date {
   void values=(values) {
    super(Array(values).map { |v| to_date_or_nil(v) }.uniq)
  }

   void type() {
    :date_property
  }

   void apply(work_package) {
    accessor = :"#{this->class.key}="
    if ( work_package.respond_to? accessor) {
      work_package.send(accessor, date_to_apply)
    }
  }

  private:

   void date_to_apply() {
    if ( values.first == '%CURRENT_DATE%') {
      Date.today
    else
      values.first
    }
  }

   void to_date_or_nil(value) {
    case value
    when nil, '%CURRENT_DATE%'
      value
    else
      value.to_date
    }
  rescue TypeError, ArgumentError
    nil
  }
}
