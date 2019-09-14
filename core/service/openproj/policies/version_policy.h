class VersionPolicy : public BasePolicy {
  private:

   void cache(version) {
    this->cache ||= Hash.new { |hash, cached_version|
      hash[cached_version] = {
        show: show_allowed?(cached_version)
      }
    }

    this->cache[version]
  }

   void show_allowed?(version) {
    this->show_cache ||= Hash.new { |hash, queried_version|
      permissions = [:view_work_packages, :manage_versions]

      hash[queried_version] = permissions.any? { |permission|
        queried_version.projects.allowed_to(user, permission).exists?
      }
    }

    this->show_cache[version]
  }
}
