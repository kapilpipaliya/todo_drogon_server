#pragma once
//
// Implements a repository factory for building temporary and permanent repositories.
namespace openproj {
namespace service {
namespace Scm{
class RepositoryFactoryService {
//  attr_reader :project, :params, :repository

//   RepositoryFactoryService(project, params) {
//    this->project = project
//    this->params = params
//  }

  //
  // Build a full repository from a given scm_type
  // and persists it.
  //
  // @return [Boolean] true iff the repository was built
//   void build_and_save() {
//    build_guarded {
//      repository = build_with_type(params.fetch(:scm_type).to_sym)
//      if ( repository.save) {
//        repository
//      else
//        raise OpenProject::Scm::Exceptions::RepositoryBuildError.new(
//          repository.errors.full_messages.join("\n")
//        )
//      }
//    }
//  }

  //
  // Build a temporary repository used only for determining availabe settings and types
  // of that particular vendor.
  //
  // @return [Boolean] true iff the repository was built
//   void build_temporary() {
//    build_guarded {
//      build_with_type(nil)
//    }
//  }

//   void build_error() {
//    I18n.t('repositories.errors.build_failed', reason: this->build_failed_msg)
//  }

  private:

  //
  // Helper to actually build the repository and return it.
  // May raise +OpenProject::Scm::Exceptions::RepositoryBuildError+ internally.
  //
  // @param [Symbol] scm_type Type to build the repository with. May be nil
  //                          during temporary build
//   void build_with_type(scm_type) {
//    Repository.build(
//      project,
//      params.fetch(:scm_vendor).to_sym,
//      params.fetch(:repository, {}),
//      scm_type
//    )
//  }

//   void build_guarded() {
//    this->repository = yield
//    this->repository.present?
//  rescue OpenProject::Scm::Exceptions::RepositoryBuildError => e
//    this->build_failed_msg = e.message
//    nil
//  }
};
}
}
}
