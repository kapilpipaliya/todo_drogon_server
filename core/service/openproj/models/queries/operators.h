namespace Queries::Operators {
  operators = [
    Queries::Operators::GreaterOrEqual,
    Queries::Operators::LessOrEqual,
    Queries::Operators::Equals,
    Queries::Operators::NotEquals,
    Queries::Operators::None,
    Queries::Operators::All,
    Queries::Operators::Contains,
    Queries::Operators::NotContains,
    Queries::Operators::InLessThan,
    Queries::Operators::InMoreThan,
    Queries::Operators::In,
    Queries::Operators::Today,
    Queries::Operators::ThisWeek,
    Queries::Operators::LessThanAgo,
    Queries::Operators::MoreThanAgo,
    Queries::Operators::Ago,
    Queries::Operators::OnDate,
    Queries::Operators::BetweenDate,
    Queries::Operators::Everywhere,
    Queries::Operators::Relates,
    Queries::Operators::Duplicates,
    Queries::Operators::Duplicated,
    Queries::Operators::Blocks,
    Queries::Operators::Blocked,
    Queries::Operators::Follows,
    Queries::Operators::Precedes,
    Queries::Operators::Includes,
    Queries::Operators::PartOf,
    Queries::Operators::Requires,
    Queries::Operators::Required,
    Queries::Operators::Parent,
    Queries::Operators::Children
  ]

  OPERATORS = Hash[*(operators.map { |o| [o.symbol.to_s, o] }).flatten].freeze
}
