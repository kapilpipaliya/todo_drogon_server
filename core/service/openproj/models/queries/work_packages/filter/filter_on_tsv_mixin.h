namespace Queries::WorkPackages::Filter::FilterOnTsvMixin {
   void concatenation() {
    case operator
    when '~'
      :and
    when '!~'
      :and_not
    }
  }
}