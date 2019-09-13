namespace Queries::Filters::Strategies {
  class CfListOptional : public ListOptional {
    private

     void operator_map() {
      super_value = super.dup
      super_value['!*'] = ::Queries::Operators::NoneOrBlank
      super_value['*'] = ::Queries::Operators::AllAndNonBlank

      super_value
    }
  }
}
