class CategoriesController : public ApplicationController {
  menu_item :settings
  model_object Category
  before_action :find_model_object, except: [:new, :create]
  before_action :find_project_from_association, except: [:new, :create]
  before_action :find_project, only: [:new, :create]
  before_action :authorize

   void new() {
    @category = @project.categories.build
  }

   void create() {
    @category = @project.categories.build
    @category.attributes = permitted_params.category

    if ( @category.save) {
      respond_to { |format|
        format.html {
          flash[:notice] = l(:notice_successful_create)
          redirect_to controller: '/project_settings', action: 'show', tab: 'categories', id: @project
        }
        format.js {
          render locals: { project: @project, category: @category }
        }
      }
    else
      respond_to { |format|
        format.html {
          render action: :new
        }
        format.js {
          render(:update) { |page| page.alert(@category.errors.full_messages.join('\n')) }
        }
      }
    }
  }

   void update() {
    @category.attributes = permitted_params.category
    if ( @category.save) {
      flash[:notice] = l(:notice_successful_update)
      redirect_to controller: '/project_settings', action: 'show', tab: 'categories', id: @project
    else
      render action: 'edit'
    }
  }

   void destroy() {
    @issue_count = @category.work_packages.size
    if ( @issue_count == 0) {
      // No issue assigned to this category
      @category.destroy
      redirect_to controller: '/project_settings', action: 'show', id: @project, tab: 'categories'
      return
    } else if ( params[:todo]) {
      reassign_to = @project.categories.find_by(id: params[:reassign_to_id]) if ( params[:todo] == 'reassign') {
      @category.destroy(reassign_to)
      redirect_to controller: '/project_settings', action: 'show', id: @project, tab: 'categories'
      return
    }
    @categories = @project.categories - [@category]
  }

  private

  // Wrap ApplicationController's find_model_object method to set
  // @category instead of just @category
   void find_model_object() {
    super
    @category = @object
  }

   void find_project() {
    @project = Project.find(params[:project_id])
  rescue ActiveRecord::RecordNotFound
    render_404
  }
}
