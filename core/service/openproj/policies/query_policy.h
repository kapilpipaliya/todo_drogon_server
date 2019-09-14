class QueryPolicy : public BasePolicy {
  private:

   void cache(query) {
    @cache ||= Hash.new { |hash, cached_query|
      hash[cached_query] = {
        show: viewable?(cached_query),
        update: persisted_and_own_or_public?(cached_query),
        destroy: persisted_and_own_or_public?(cached_query),
        create: create_allowed?(cached_query),
        create_new: create_new_allowed?(cached_query),
        publicize: publicize_allowed?(cached_query),
        depublicize: depublicize_allowed?(cached_query),
        star: persisted_and_own_or_public?(cached_query),
        unstar: persisted_and_own_or_public?(cached_query),
        reorder_work_packages: reorder_work_packages?(cached_query)
      }
    }

    @cache[query]
  }

   void persisted_and_own_or_public?(query) {
    query.persisted? &&
      (
        (save_queries_allowed?(query) && query.user == user) ||
        public_manageable_query?(query)
      )
  }

   void viewable?(query) {
    view_work_packages_allowed?(query) &&
      (query.is_public? || query.user == user)
  }

   void create_allowed?(query) {
    query.new_record? && create_new_allowed?(query)
  }

   void create_new_allowed?(query) {
    save_queries_allowed?(query)
  }

   void publicize_allowed?(query) {
    !query.is_public &&
      query.user_id == user.id &&
      manage_public_queries_allowed?(query)
  }

   void depublicize_allowed?(query) {
    public_manageable_query?(query)
  }

   void public_manageable_query?(query) {
    query.is_public &&
      manage_public_queries_allowed?(query)
  }

   void reorder_work_packages?(query) {
    persisted_and_own_or_public?(query) || edit_work_packages_allowed?(query)
  }

   void view_work_packages_allowed?(query) {
    @view_work_packages_cache ||= Hash.new { |hash, project|
      hash[project] = user.allowed_to?(:view_work_packages, project, global: project.nil?)
    }

    @view_work_packages_cache[query.project]
  }

   void edit_work_packages_allowed?(query) {
    @edit_work_packages_cache ||= Hash.new { |hash, project|
      hash[project] = user.allowed_to?(:edit_work_packages, project, global: project.nil?)
    }

    @edit_work_packages_cache[query.project]
  }

   void save_queries_allowed?(query) {
    @save_queries_cache ||= Hash.new { |hash, project|
      hash[project] = user.allowed_to?(:save_queries, project, global: project.nil?)
    }

    @save_queries_cache[query.project]
  }

   void manage_public_queries_allowed?(query) {
    @manage_public_queries_cache ||= Hash.new { |hash, project|
      hash[project] = user.allowed_to?(:manage_public_queries, project, global: project.nil?)
    }

    @manage_public_queries_cache[query.project]
  }
}
