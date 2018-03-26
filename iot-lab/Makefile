# Add new repositories in REPOS variable
APP_REPOS = fault-partition
EXTERN_REPOS = riot
RIOT_BRANCH = 2018.01-branch-klec
REPOS = $(APP_REPOS) $(EXTERN_REPOS)

SETUP_REPOS = $(sort $(addprefix setup-, $(REPOS)))

help:
	@printf "\nWelcome iot development environment setup.\n\n"
	@printf "targets:\n"
	@for setup_cmd in $(SETUP_REPOS); do \
		printf "\t$${setup_cmd}\n";    \
	done
	@echo  ""
	@printf "\tpull\n"
	@echo  ""
all: $(addprefix setup-, $(REPOS))


KL_CODE_URL = http://www.klec.com.cn:10000

# External repositories
setup-riot: parts/RIOT
parts/RIOT:
	git clone -b $(RIOT_BRANCH) $(KL_CODE_URL)/embedded/RIOT.git $@

# app repositories
$(addprefix setup-, $(APP_REPOS)): setup-%: parts/%
parts/%:
	git clone $(KL_CODE_URL)/embedded/$*.git $@


# Pull in new changes
pull: $(subst parts/,pull-,$(wildcard parts/*))
	git pull
pull-%: parts/%
	cd $^; git pull; cd -


.PHONY: help setup-% pull pull-% tests tests-%
.PRECIOUS: parts/%