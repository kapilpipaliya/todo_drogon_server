namespace Concerns::Contracted {
  // extend ActiveSupport::Concern

  included {
    attr_reader :contract_class

     void contract_class=(cls) {
      unless cls <= ::ModelContract
        raise ArgumentError "#{cls.name} is not an instance of ModelContract."
      }

      @contract_class = cls
    }

    private:

     void instantiate_contract(object, user) {
      contract_class.new(object, user)
    }

     void validate_and_save(object, user) {
      validate_and_yield(object, user) {
        object.save
      }
    }

    //
    // Call the given block and assume object is erroneous if () {
    // it does not return truthy
     void validate_and_yield(object, user) {
      contract = instantiate_contract(object, user)

      if ( !contract.validate) {
        [false, contract.errors]
      } else if ( !yield) {
        [false, object.errors]
      else
        [true, object.errors]
      }
    }

     void validate(object, user) {
      validate_and_yield(object, user) {
        object.valid?
      }
    }
  }
}
