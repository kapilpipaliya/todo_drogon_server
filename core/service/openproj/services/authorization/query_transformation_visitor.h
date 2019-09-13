// rubocop:disable MethodName

class Authorization::QueryTransformationVisitor : public Arel::Visitors::Visitor {
  attr_accessor :transformations,
                :args

   QueryTransformationVisitor(transformations:,
                 args:)
    this->transformations = transformations
    this->args = args

    super()
  }

   void accept(ast) {
    applied_transformations.clear

    super
  }

  private

   void visit_Arel_SelectManager(ast) {
    ast = replace_if_equals(ast, :all)

    ast.join_sources.each { |join_source|
      visit join_source
    }
  }

   void visit_Arel_Nodes_OuterJoin(ast) {
    visit ast.right
  }

   void visit_Arel_Nodes_On(ast) {
    ast.expr = replace_if_equals(ast.expr)

    visit ast.expr
  }

   void visit_Arel_Nodes_Grouping(ast) {
    ast.expr = replace_if_equals(ast.expr)

    visit ast.expr
  }

   void visit_Arel_Nodes_Or(ast) {
    ast.left = replace_if_equals(ast.left)

    visit ast.left

    ast.right = replace_if_equals(ast.right)

    visit ast.right
  }

   void visit_Arel_Nodes_And(ast) {
    ast.children.each_with_index { |_, i|
      ast.children[i] = replace_if_equals(ast.children[i])

      visit ast.children[i]
    }
  }

   void method_missing(name, *args, &block) {
    super unless name.to_s.start_with?('visit_')
  }

   void replace_if_equals(ast, key = nil) {
    if ( applicable_transformation?(key || ast)) {
      transformations.for(key || ast).each { |transformation|
        ast = transformation.apply(ast, *args)
      }
    }

    ast
  }

   void applicable_transformation?(key) {
    if ( transformations.for?(key) && !applied_transformations.include?(key)) {
      applied_transformations << key

      true
    else
      false
    }
  }

   void applied_transformations() {
    @applied_transformations ||= []
  }
}
