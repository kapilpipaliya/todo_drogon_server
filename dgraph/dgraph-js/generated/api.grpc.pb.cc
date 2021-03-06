// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: api.proto

#include "api.pb.h"
#include "api.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/method_handler_impl.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace api {

static const char* Dgraph_method_names[] = {
  "/api.Dgraph/Login",
  "/api.Dgraph/Query",
  "/api.Dgraph/Alter",
  "/api.Dgraph/CommitOrAbort",
  "/api.Dgraph/CheckVersion",
};

std::unique_ptr< Dgraph::Stub> Dgraph::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< Dgraph::Stub> stub(new Dgraph::Stub(channel));
  return stub;
}

Dgraph::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_Login_(Dgraph_method_names[0], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_Query_(Dgraph_method_names[1], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_Alter_(Dgraph_method_names[2], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_CommitOrAbort_(Dgraph_method_names[3], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_CheckVersion_(Dgraph_method_names[4], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status Dgraph::Stub::Login(::grpc::ClientContext* context, const ::api::LoginRequest& request, ::api::Response* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_Login_, context, request, response);
}

void Dgraph::Stub::experimental_async::Login(::grpc::ClientContext* context, const ::api::LoginRequest* request, ::api::Response* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_Login_, context, request, response, std::move(f));
}

void Dgraph::Stub::experimental_async::Login(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::api::Response* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_Login_, context, request, response, std::move(f));
}

void Dgraph::Stub::experimental_async::Login(::grpc::ClientContext* context, const ::api::LoginRequest* request, ::api::Response* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_Login_, context, request, response, reactor);
}

void Dgraph::Stub::experimental_async::Login(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::api::Response* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_Login_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::api::Response>* Dgraph::Stub::AsyncLoginRaw(::grpc::ClientContext* context, const ::api::LoginRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::api::Response>::Create(channel_.get(), cq, rpcmethod_Login_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::api::Response>* Dgraph::Stub::PrepareAsyncLoginRaw(::grpc::ClientContext* context, const ::api::LoginRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::api::Response>::Create(channel_.get(), cq, rpcmethod_Login_, context, request, false);
}

::grpc::Status Dgraph::Stub::Query(::grpc::ClientContext* context, const ::api::Request& request, ::api::Response* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_Query_, context, request, response);
}

void Dgraph::Stub::experimental_async::Query(::grpc::ClientContext* context, const ::api::Request* request, ::api::Response* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_Query_, context, request, response, std::move(f));
}

void Dgraph::Stub::experimental_async::Query(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::api::Response* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_Query_, context, request, response, std::move(f));
}

void Dgraph::Stub::experimental_async::Query(::grpc::ClientContext* context, const ::api::Request* request, ::api::Response* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_Query_, context, request, response, reactor);
}

void Dgraph::Stub::experimental_async::Query(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::api::Response* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_Query_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::api::Response>* Dgraph::Stub::AsyncQueryRaw(::grpc::ClientContext* context, const ::api::Request& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::api::Response>::Create(channel_.get(), cq, rpcmethod_Query_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::api::Response>* Dgraph::Stub::PrepareAsyncQueryRaw(::grpc::ClientContext* context, const ::api::Request& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::api::Response>::Create(channel_.get(), cq, rpcmethod_Query_, context, request, false);
}

::grpc::Status Dgraph::Stub::Alter(::grpc::ClientContext* context, const ::api::Operation& request, ::api::Payload* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_Alter_, context, request, response);
}

void Dgraph::Stub::experimental_async::Alter(::grpc::ClientContext* context, const ::api::Operation* request, ::api::Payload* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_Alter_, context, request, response, std::move(f));
}

void Dgraph::Stub::experimental_async::Alter(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::api::Payload* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_Alter_, context, request, response, std::move(f));
}

void Dgraph::Stub::experimental_async::Alter(::grpc::ClientContext* context, const ::api::Operation* request, ::api::Payload* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_Alter_, context, request, response, reactor);
}

void Dgraph::Stub::experimental_async::Alter(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::api::Payload* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_Alter_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::api::Payload>* Dgraph::Stub::AsyncAlterRaw(::grpc::ClientContext* context, const ::api::Operation& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::api::Payload>::Create(channel_.get(), cq, rpcmethod_Alter_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::api::Payload>* Dgraph::Stub::PrepareAsyncAlterRaw(::grpc::ClientContext* context, const ::api::Operation& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::api::Payload>::Create(channel_.get(), cq, rpcmethod_Alter_, context, request, false);
}

::grpc::Status Dgraph::Stub::CommitOrAbort(::grpc::ClientContext* context, const ::api::TxnContext& request, ::api::TxnContext* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_CommitOrAbort_, context, request, response);
}

void Dgraph::Stub::experimental_async::CommitOrAbort(::grpc::ClientContext* context, const ::api::TxnContext* request, ::api::TxnContext* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_CommitOrAbort_, context, request, response, std::move(f));
}

void Dgraph::Stub::experimental_async::CommitOrAbort(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::api::TxnContext* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_CommitOrAbort_, context, request, response, std::move(f));
}

void Dgraph::Stub::experimental_async::CommitOrAbort(::grpc::ClientContext* context, const ::api::TxnContext* request, ::api::TxnContext* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_CommitOrAbort_, context, request, response, reactor);
}

void Dgraph::Stub::experimental_async::CommitOrAbort(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::api::TxnContext* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_CommitOrAbort_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::api::TxnContext>* Dgraph::Stub::AsyncCommitOrAbortRaw(::grpc::ClientContext* context, const ::api::TxnContext& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::api::TxnContext>::Create(channel_.get(), cq, rpcmethod_CommitOrAbort_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::api::TxnContext>* Dgraph::Stub::PrepareAsyncCommitOrAbortRaw(::grpc::ClientContext* context, const ::api::TxnContext& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::api::TxnContext>::Create(channel_.get(), cq, rpcmethod_CommitOrAbort_, context, request, false);
}

::grpc::Status Dgraph::Stub::CheckVersion(::grpc::ClientContext* context, const ::api::Check& request, ::api::Version* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_CheckVersion_, context, request, response);
}

void Dgraph::Stub::experimental_async::CheckVersion(::grpc::ClientContext* context, const ::api::Check* request, ::api::Version* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_CheckVersion_, context, request, response, std::move(f));
}

void Dgraph::Stub::experimental_async::CheckVersion(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::api::Version* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_CheckVersion_, context, request, response, std::move(f));
}

void Dgraph::Stub::experimental_async::CheckVersion(::grpc::ClientContext* context, const ::api::Check* request, ::api::Version* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_CheckVersion_, context, request, response, reactor);
}

void Dgraph::Stub::experimental_async::CheckVersion(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::api::Version* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_CheckVersion_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::api::Version>* Dgraph::Stub::AsyncCheckVersionRaw(::grpc::ClientContext* context, const ::api::Check& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::api::Version>::Create(channel_.get(), cq, rpcmethod_CheckVersion_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::api::Version>* Dgraph::Stub::PrepareAsyncCheckVersionRaw(::grpc::ClientContext* context, const ::api::Check& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::api::Version>::Create(channel_.get(), cq, rpcmethod_CheckVersion_, context, request, false);
}

Dgraph::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Dgraph_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Dgraph::Service, ::api::LoginRequest, ::api::Response>(
          std::mem_fn(&Dgraph::Service::Login), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Dgraph_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Dgraph::Service, ::api::Request, ::api::Response>(
          std::mem_fn(&Dgraph::Service::Query), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Dgraph_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Dgraph::Service, ::api::Operation, ::api::Payload>(
          std::mem_fn(&Dgraph::Service::Alter), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Dgraph_method_names[3],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Dgraph::Service, ::api::TxnContext, ::api::TxnContext>(
          std::mem_fn(&Dgraph::Service::CommitOrAbort), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Dgraph_method_names[4],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Dgraph::Service, ::api::Check, ::api::Version>(
          std::mem_fn(&Dgraph::Service::CheckVersion), this)));
}

Dgraph::Service::~Service() {
}

::grpc::Status Dgraph::Service::Login(::grpc::ServerContext* context, const ::api::LoginRequest* request, ::api::Response* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status Dgraph::Service::Query(::grpc::ServerContext* context, const ::api::Request* request, ::api::Response* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status Dgraph::Service::Alter(::grpc::ServerContext* context, const ::api::Operation* request, ::api::Payload* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status Dgraph::Service::CommitOrAbort(::grpc::ServerContext* context, const ::api::TxnContext* request, ::api::TxnContext* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status Dgraph::Service::CheckVersion(::grpc::ServerContext* context, const ::api::Check* request, ::api::Version* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace api

