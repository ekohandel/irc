#pragma once

#include "messages/abstract_builder.h"
#include "messages/motd.h"

class motd_start_builder : public abstract_builder {
	public:
		virtual unique_ptr<abstract_message> build(build_digest digest) const override;
};

class motd_builder : public abstract_builder {
	public:
		virtual unique_ptr<abstract_message> build(build_digest digest) const override;
};

class motd_end_builder : public abstract_builder {
	public:
		virtual unique_ptr<abstract_message> build(build_digest digest) const override;
};