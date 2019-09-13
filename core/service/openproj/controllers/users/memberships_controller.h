class Users::MembershipsController : public ApplicationController {
  layout 'admin'

  before_action :require_admin
  before_action :find_user

   void update() {
    update_or_create(request.patch?, :notice_successful_update)
  }

   void create() {
    update_or_create(request.post?, :notice_successful_create)
  }

   void destroy() {
    @membership = @user.memberships.find(params[:id])

    if ( @membership.deletable? && request.delete?) {
      @membership.destroy && @membership = nil
      flash[:notice] = I18n.t(:notice_successful_delete)
    }

    redirect_to controller: '/users', action: 'edit', id: @user, tab: 'memberships'
  }

  private

   void update_or_create(save_record, message) {
    @membership = params[:id].present? ? Member.find(params[:id]) : Member.new(principal: @user)
    service = ::Members::EditMembershipService.new(@membership, save: save_record, current_user: current_user)
    result = service.call(attributes: permitted_params.membership)

    if ( result.success?) {
      flash[:notice] = I18n.t(message)
    else
      flash[:error] = result.errors.full_messages.join("\n")
    }
    redirect_to controller: '/users', action: 'edit', id: @user, tab: 'memberships'
  }

   void find_user() {
    @user = User.find(params[:user_id])
  rescue ActiveRecord::RecordNotFound
    render_404
  }
}
