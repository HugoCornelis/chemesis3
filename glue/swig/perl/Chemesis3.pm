#!/usr/bin/perl -w
#!/usr/bin/perl -w -d:ptkdb
#

package Chemesis3;


use strict;


# a default config at your convenience, not obligation to use it

our $config
    = {
       concentration_gate_end => 0.3,
       concentration_gate_start => 4e-5,
       interval_default_end => (0.05),
       interval_default_entries => 3000,
       interval_default_start => (-0.1),
       reporting => {
		     file => undef,
		     granularity => 1,
		    },
       steps => 10,
       time_step => (2e-5),
      };


sub addressable
{
    my $self = shift;

    my $fieldinfo = shift;

    my $result = $self->{chemesis3}->Chemesis3AddressVariable($fieldinfo->{serial}, $fieldinfo->{type});

    return $result;
}


# sub advance
# {
#     my $self = shift;

#     my $scheduler = shift;

#     my $time = shift;

#     my $result = $self->{chemesis3}->Chemesis3Heccs($time);

#     return $result;
# }


sub backend
{
    my $self = shift;

    return $self->{chemesis3};
}


sub compile
{
    my $self = shift;

    my $scheduler = shift;

    my $options = shift;

#     # if a channel current or conductance must be calculated

#     my $has_current_output;

#     if ($scheduler)
#     {
# 	my $outputs = $scheduler->get_engine_outputs($self);

# 	$has_current_output
# 	    = scalar
# 		grep
# 		{
# 		    (
# 		     $_->{field} eq 'I'
# 		     or $_->{field} eq 'G'
# 		     or $_->{field} eq 'current'
# 		     or $_->{field} eq 'conductance'
# 		    )
# 		}
# 		    @$outputs;
#     }

#     if ($has_current_output)
#     {
# 	# set option that enables these calculations

# 	my $chemesis3_options = $self->{chemesis3}->swig_ho_get();

# 	my $options = $chemesis3_options->swig_iOptions_get();

# 	$options |= $SwiggableChemesis3::CHEMESIS3_OPTION_ENABLE_INDIVIDUAL_CURRENTS;

# 	$chemesis3_options->swig_iOptions_set($options);

# 	#! swig works by reference, so setting in ho also sets in chemesis3
#     }

    # get status

    my $status = $self->{chemesis3}->swig_iStatus_get();

    if ($status le $SwiggableChemesis3::CHEMESIS3_STATUS_PHASE_1)
    {
	# compile

	my $compilation_result = $self->compile1();

	if ($compilation_result)
	{
	    return $compilation_result;
	}
    }

    # continue compile

    return $self->compile2();
}


sub compile1
{
    my $self = shift;

    if ($self->{chemesis3}->Chemesis3CompileP1())
    {
	return '';
    }
    else
    {
	return "Chemesis3CompileP1() failed";
    }
}


sub compile2
{
    my $self = shift;

#     if ($self->{chemesis3}->Chemesis3CompileP2())
    {
	return $self->compile3();
    }
#     else
    {
	return "Chemesis3CompileP2() failed";
    }
}


sub compile3
{
    my $self = shift;

#     if ($self->{chemesis3}->Chemesis3CompileP3())
    {
	return '';
    }
#     else
    {
	return "Chemesis3CompileP3() failed";
    }
}


sub connect
{
    my $self = shift;

    my $scheduler = shift;

    my $result = 1;

#     # find the event distributor and queuer

#     my $des = $scheduler->{schedule}->[0];

    return '';
}


sub deserialize2
{
    my $old_self = shift;

    my $filename = shift;

    my $backend = SwiggableChemesis3::Chemesis3DeserializeFromFilename($filename);

    my $self
	= {
	   %$old_self,
	   chemesis3 => $backend,
	  };

    bless $self, __PACKAGE__;

    return $self;
}


sub deserialize_state
{
    my $self = shift;

    my $filename = shift;

    my $result = 1;

    my $backend = $self->backend();

    my $file = SwiggableChemesis3::Chemesis3SerializationOpenRead($filename);

    $result = $result && $backend->Chemesis3DeserializeState($file);

    if (SwiggableChemesis3::Chemesis3SerializationClose($file) != 0)
    {
	$result = 0;
    }

    return $result;
}


sub dump
{
    my $self = shift;

    #t not sure how it could be possible to use $file, but anyway,
    #t placeholder for the idea.

    my $file = shift;

    my $selection = shift;

    if (!defined $selection)
    {
# 	$self->{chemesis3}->Chemesis3DumpV();
    }
    else
    {
# 	$self->{chemesis3}->Chemesis3Dump($file, $selection);
    }
}


sub finish
{
    my $self = shift;

    #! that is ok.
}


sub get_driver
{
    my $self = shift;

    my $result
	= {
	   data => $self->{chemesis3}->chemesis3_get_driver_data(),
	   method => $self->{chemesis3}->chemesis3_get_driver_method(),
# 	   data => \&SwiggableChemesis3::Chemesis3Heccs$self->{chemesis3},
# 	   method => \&SwiggableChemesis3::Chemesis3Heccs,
	  };

    return $result;
}


sub get_time_step
{
    my $self = shift;

    # get time step from the low level solver

    my $result = $self->{chemesis3}->swig_dStep_get();

    # return result

    return $result;
}


sub initiate
{
    my $self = shift;

    $self->{chemesis3}->Chemesis3Initiate();
}


sub new
{
    my $package = shift;

    my $settings = shift;

    #! note that ignored settings are ignored because of an empty translator.

    #! what setting keys get ignored again ?

    my $result = Chemesis3::Chemesis3::new($package, $settings, @_, );

    # if construction was successful

    if (ref $result)
    {
	bless $result, $package;

	my $event_distributor_backend;

# 	if ($settings->{event_distributor}->{event_distributor_backend})
# 	{
# 	    $event_distributor_backend = $settings->{event_distributor}->{event_distributor_backend}->backend();
# 	}

	my $event_queuer_backend;

# 	if ($settings->{event_queuer}->{event_queuer_backend})
# 	{
# 	    $event_queuer_backend = $settings->{event_queuer}->{event_queuer_backend}->backend();
# 	}

	# if there is a model source

	my $model_source = $settings->{model_source};

	if (exists $model_source->{service_name})
	{
	    # if setting up from a model container

	    my $service_name = $model_source->{service_name};

	    if ($service_name eq 'model_container')
	    {
		my $service_backend = $model_source->{service_backend}->backend();

		my $modelname = $model_source->{modelname};

		my $chemesis3_backend = $result->backend();

		# setup the interface to build an intermediary

		my $success = SwiggableChemesis3::Chemesis3Construct($chemesis3_backend, $service_backend, $modelname, $event_distributor_backend, $event_queuer_backend);

		if (!$success)
		{
		    return "Chemesis3Construct() from the model_container failed";
		}

		# if there was an intermediary

		if ($settings->{intermediary})
		{
		    # set status: CHEMESIS3_STATUS_PHASE_2

		    $result->{chemesis3}->swig_iStatus_set($SwiggableChemesis3::CHEMESIS3_STATUS_PHASE_2);
		}
	    }

	    # if setting up from an inlined chemesis3_intermediary

	    elsif ($service_name eq 'chemesis3_intermediary')
	    {
		# get reference to the inlined chemesis3_intermediary

		my $service_backend = $model_source->{service_backend};

		my $intermediary = $service_backend->backend();

		# get low-level intermediary

		my $intermediary_backend = $intermediary->backend();

		# link the chemesis3 with the intermediary

		my $chemesis3_backend = $result->backend();

		$chemesis3_backend->swig_inter_set($intermediary_backend);

		$chemesis3_backend->swig_iStatus_set($SwiggableChemesis3::CHEMESIS3_STATUS_PHASE_2);

		# set the chemesis3 name

		my $modelname = $model_source->{modelname};

		$chemesis3_backend->swig_pcName_set($modelname);

		my $success = 1;

		if (!$success)
		{
		    return "Chemesis3Construct() from chemesis3_intermediary failed";
		}
	    }
	    else
	    {
		# no other services supported

		return
"Chemesis3 does only know a model_container as a service.  If you need a
different service, you have to install the appropriate integrator
plugin for Chemesis3, and let the perl package know how to call the
integrator.";
	    }
	}

	# if was a direct initialization

	else
	{
	    # if there was an intermediary

	    if ($settings->{intermediary})
	    {
		# set status: CHEMESIS3_STATUS_PHASE_2

		$result->{chemesis3}->swig_iStatus_set($SwiggableChemesis3::CHEMESIS3_STATUS_PHASE_2);
	    }
	}
    }

    return $result;
}


sub report
{
    #t call ->dump() with dump options in this object.

    my $self = shift;

    my $scheduler = shift;

    my $options = shift;

    my $result = 1;

    if ($options->{verbose})
    {
	my $header;

	my $steps = $options->{steps};

	my $reporting = $self->{configuration}->{reporting};

	if (!defined $steps)
	{
	    $header = "Initiated\n";
	}
	else
	{
	    if ($steps eq -1)
	    {
		if ($self->{final_report})
		{
		    $header = "-------\nFinal Iteration\n";
		}
	    }
	    else
	    {
		my $reporting_granularity = $reporting->{granularity} || 1;

		if (($steps % $reporting_granularity) == 0)
		{
		    $header = "-------\nIteration $steps\n";
		}
		else
		{
		    $self->{final_report} = 1;
		}
	    }
	}

	if ($header)
	{
	    my $file = $reporting->{file};

	    if (defined $file)
	    {
		print $file $header;
	    }
	    else
	    {
		print $header;
	    }

	    my $tested_things = $reporting->{tested_things};

	    $result = $self->dump($file, $tested_things);
	}
    }

    return $result;
}


sub set_addressable
{
    my $self = shift;

    my $fieldinfo = shift;

    my $value = shift;

    my $result = $self->{chemesis3}->Chemesis3AddressableSet($fieldinfo->{serial}, $fieldinfo->{type}, $value);

    return $result;
}


sub serialize
{
    my $self = shift;

    my $filename = shift;

    my $backend = $self->backend();

    return $backend->Chemesis3SerializeToFilename($filename);
}


sub serialize_state
{
    my $self = shift;

    my $filename = shift;

    my $result = 1;

    my $backend = $self->backend();

    my $file = SwiggableChemesis3::Chemesis3SerializationOpenWrite($filename);

    $result = $result && $backend->Chemesis3SerializeCompartmentState($file);

    $result = $result && $backend->Chemesis3SerializeMechanismState($file);

    if (SwiggableChemesis3::Chemesis3SerializationClose($file) != 0)
    {
	$result = 0;
    }

    return $result;
}


sub step
{
    my $self = shift;

    my $current_time = $self->{chemesis3}->swig_dTime_get();

    my $current_step = $self->{chemesis3}->swig_dStep_get();

    my $small_thing = $current_step / 2;

    my $target_time = $current_time + $current_step - $small_thing;

    $self->{chemesis3}->Chemesis3Advance($target_time);
}


sub version
{
    # $Format: "    my $version=\"${package}-${label}\";"$
    my $version="chemesis3-alpha";


    return $version;
}


package Chemesis3::Component;


use SwiggableChemesis3;


#define CHEMESIS3_DUMP_ALL (0xffffffff & ~(CHEMESIS3_DUMP_SERVICE | CHEMESIS3_DUMP_TABLE_GATE_TABLES))

# our $SwiggableChemesis3::CHEMESIS3_DUMP_ALL = (0xffffffff & ~(CHEMESIS3_DUMP_SERVICE | CHEMESIS3_DUMP_TABLE_GATE_TABLES));


my $chemesis3_mapping
    = {
       concentration_activator => {
				   constructor_settings => {
							    iTable => -1,
							   },
				   internal_name => 'ConcentrationActivator',
				   translators => {
						   parameters => {
								  source => 'activator_parameters',
								  target => 'parameters',
								 },
						  },
				  },
       activator_parameters => {
				internal_name => 'ActivatorParameters',
			       },
       callout => {
		   internal_name => 'Callout',
		   translators => {
				   external_function => {
							 convertor =>
							 sub
							 {
							     my $target = shift;

							     my $value = shift;

							     return $value;
							 },
							 target => 'pef',
							},
				   external_results => {
							target => 'per',
						       },
				   internal_results => {
							target => 'pir',
						       },
				  },
		   type_number => $SwiggableChemesis3::MATH_TYPE_CallOut_conductance_current,
		  },
       channel_activation_concentration => {
					    constructor_settings => {
								     iPool => -1,
								     iReversalPotential => -1,
								    },
					    internal_name => 'ChannelActConc',
					    translators => {
							    activation => {
									   source => 'powered_gate_concept',
									   target => 'pgc',
									  },
							    powered_activator => {
										  source => 'powered_activator_concept',
										  target => 'pac',
										 },
							   },
					    type_number => $SwiggableChemesis3::MATH_TYPE_ChannelActConc,
					   },
       channel_activation_inactivation => {
					   constructor_settings => {
								    iPool => -1,
								    iReversalPotential => -1,
								   },
					   internal_name => 'ChannelActInact',
					   translators => {
							   activation => {
									  source => 'powered_gate_concept',
									  target => 'pgcActivation',
									 },
							   inactivation => {
									    source => 'powered_gate_concept',
									    target => 'pgcInactivation',
									   },
							  },
					   type_number => $SwiggableChemesis3::MATH_TYPE_ChannelActInact,
					  },
       compartment => {
		       constructor_settings => {
						iParent => -1,
					       },
		       internal_name => 'Compartment',
		       type_number => $SwiggableChemesis3::MATH_TYPE_Compartment,
		      },
       exponential_decay => {
			     constructor_settings => {
						      piExternal => [
								     map { -1, } 1 .. $SwiggableChemesis3::EXPONENTIALDECAY_CONTRIBUTORS,
								    ],
						     },
			     internal_name => 'ExponentialDecay',
			     translators => {
					     piExternal => {
							    convertor =>
							    sub
							    {
								my $target = shift;

								my $value = shift;

								my $result = SwiggableChemesis3::int_array($SwiggableChemesis3::EXPONENTIALDECAY_CONTRIBUTORS);

								foreach my $external_index (0 .. $SwiggableChemesis3::EXPONENTIALDECAY_CONTRIBUTORS - 1)
								{
								    my $external = $value->[$external_index];

								    if (!defined $external)
								    {
									$external = -1;
								    }

								    SwiggableChemesis3::int_set($result, $external_index, $external);
								}

								return $result;
							    },
							    target => 'piExternal',
							   },
					    },
			     type_number => $SwiggableChemesis3::MATH_TYPE_ExponentialDecay,
			    },
#        external_function => {
# 			    },
       external_results => {
			    internal_name => 'ExternalResults',
			   },
       gate_concept => {
			constructor_settings => {
						 iTable => -1,
						},
			internal_name => 'GateConcept',
			translators => {
					parameters => {
						       source => 'gate_concept_parameters',
						       target => 'parameters',
						      },
				       },
		       },
       gate_concept_parameters => {
				   internal_name => 'GateConceptParameters',
				   translators => {
						   A => {
							 source => 'gate_kinetic',
							 target => 'gkA',
							},
						   B => {
							 source => 'gate_kinetic',
							 target => 'gkB',
							},
						  },
				  },
       gate_kinetic => {
			constructor_settings => {
						 dHHMultExp => 1,
						},
			internal_name => 'GateKinetic',
		       },
       chemesis3 => {
		  constructor_settings => {
					   dStep => 2e-5,
# 					   options => {
# 						       dConcentrationGateEnd => $SwiggableChemesis3::CHEMESIS3_INTERVAL_CONCENTRATION_GATE_DEFAULT_END,
# 						       dConcentrationGateStart => $SwiggableChemesis3::CHEMESIS3_INTERVAL_CONCENTRATION_GATE_DEFAULT_START,
# 						       dIntervalEnd => $SwiggableChemesis3::CHEMESIS3_INTERVAL_DEFAULT_END,
# 						       dIntervalStart => $SwiggableChemesis3::CHEMESIS3_INTERVAL_DEFAULT_START,
# 						       iIntervalEntries => $SwiggableChemesis3::CHEMESIS3_INTERVAL_DEFAULT_ENTRIES,
# 						       iSmallTableSize => $SwiggableChemesis3::CHEMESIS3_INTERPOL_INTERVAL_DEFAULT_ENTRIES,

# 						       #t the default at C level is wrong, needs a careful check.

# # 						       iOptions => $SwiggableChemesis3::CHEMESIS3_OPTION_BRANCHES_FIRST_SCHEDULING,
# 						      },

					   #! this is mainly to get the tests to work ...

					   pcName => "unnamed test",
					  },
		  internal_name => 'simobj_Chemesis3',
		  translators => {
				  configuration => {
						   },

				  #t event_distributor, see model_source comments below

				  event_distributor => {
						       },

				  #t event_queuer, see model_source comments below

				  event_queuer => {
						  },

				  intermediary => {
						   target => 'inter',
						  },

				  # model_source comes from SSP, should not be translated

				  #t we should use this to translate the model_source into the TranslationServiceData or so

				  model_source => {
						  },
				  options => {
					      source => 'options',
					      target => 'ho',
					     },
				 },
		 },
       intermediary => {
			internal_name => 'Intermediary',
			translators => {
					compartments => {
							 convertor =>
							 sub
							 {
							     my $target = shift;

							     my $value = shift;

							     my $result = SwiggableChemesis3::comp_array($#$value + 1);

							     foreach my $compartment_index (0 .. $#$value)
							     {
								 my $compartment = $value->[$compartment_index];

								 my $ref = ref $compartment;

								 if ($ref =~ /^HASH/)
								 {
								     $compartment = Chemesis3::Compartment->new($compartment);
								 }

								 SwiggableChemesis3::comp_set($result, $compartment_index, $compartment->{compartment});
							     }

							     return $result;
							 },
							 target => 'pcomp',
							},
					comp2mech => {
						      convertor =>
						      sub
						      {
							  my $target = shift;

							  my $value = shift;

							  my $result = SwiggableChemesis3::int_array($#$value + 1);

							  foreach my $compartment_index (0 .. $#$value)
							  {
							      my $compartment_start = $value->[$compartment_index];

							      SwiggableChemesis3::int_set($result, $compartment_index, $compartment_start);
							  }

							  return $result;
						      },
						      target => 'piC2m',
						     },
					math_components => {
							    convertor =>
							    sub
							    {
								my $target = shift;

								my $value = shift;

								my $result = Chemesis3::MathComponentArray->new( { iMathComponents => 0, } );

								#! why again +2: 1 is from the perl $#$ operator offset, the other 1 is for the terminating -1

								my $types = SwiggableChemesis3::int_array($#$value + 2);

								# loop over all given value entries

								foreach my $math_component_index (0 .. $#$value)
								{
								    my $type = $value->[$math_component_index]->chemesis3_object()->swig_mc_get()->swig_iType_get();

								    SwiggableChemesis3::int_set($types, $math_component_index, $type);
								}

								# set the terminating -1 in the types array

								SwiggableChemesis3::int_set($types, $#$value + 1, -1);

								# allocate a math component array for these types

								$result->chemesis3_object()->MathComponentArrayCallocData($types);

								# loop over all given value entries

								foreach my $math_component_index (0 .. $#$value)
								{
								    # copy the memory of the low level entry

								    my $mc = $value->[$math_component_index]->chemesis3_object()->swig_mc_get();

								    $result->chemesis3_object()->MathComponentArraySetAdvance($mc);
								}

								# the math_component array will be set in the intermediary at C level,
								# so perl should not touch it anymore.

								$result->chemesis3_object()->DISOWN();

								return $result->chemesis3_object();
							    },
							    target => 'pmca',
							   },
				       },
		       },
       internal_results => {
			    internal_name => 'InternalResults',
			   },
       math_component_array => {
				internal_name => 'MathComponentArray',
			       },
       options => {
		   constructor_settings => {
					    dConcentrationGateEnd => $SwiggableChemesis3::CHEMESIS3_INTERVAL_CONCENTRATION_GATE_DEFAULT_END,
					    dConcentrationGateStart => $SwiggableChemesis3::CHEMESIS3_INTERVAL_CONCENTRATION_GATE_DEFAULT_START,
					    dIntervalEnd => $SwiggableChemesis3::CHEMESIS3_INTERVAL_DEFAULT_END,
					    dIntervalStart => $SwiggableChemesis3::CHEMESIS3_INTERVAL_DEFAULT_START,
					    iIntervalEntries => $SwiggableChemesis3::CHEMESIS3_INTERVAL_DEFAULT_ENTRIES,
					    iSmallTableSize => $SwiggableChemesis3::CHEMESIS3_INTERPOL_INTERVAL_DEFAULT_ENTRIES,

					    #t the default at C level is wrong, needs a careful check.

# 					    iOptions => $SwiggableChemesis3::CHEMESIS3_OPTION_BRANCHES_FIRST_SCHEDULING,
					   },
		   internal_name => 'Chemesis3Options',
		  },
       powered_activator_concept => {
				     internal_name => 'PoweredActivatorConcept',
				     translators => {
						     concentration_activator => {
										 source => 'concentration_activator',
										 target => 'ca',
										},
						    },
				    },
       powered_gate_concept => {
				internal_name => 'PoweredGateConcept',
				translators => {
						gate_concept => {
								 source => 'gate_concept',
								 target => 'gc',
								},
					       },
			       },
      };


sub new
{
    my $package = shift;

    my $subpackage = shift;

    my $type = shift;

    my $settings = shift;

    if (!exists $chemesis3_mapping->{$type})
    {
	return "$type is not a Chemesis3::Component";
    }

    # create the chemesis3 internal object

    my $internal_name = $chemesis3_mapping->{$type}->{internal_name};

    my $factory_package = "SwiggableChemesis3::$internal_name";

    my $self
	= {
	   $type => $factory_package->new(),
	  };

    # never forget to set the chemesis3 type

    my $type_number = $chemesis3_mapping->{$type}->{type_number};

    if ($type_number)
    {
	my $mc = $self->{$type}->swig_mc_get();

	$mc->swig_iType_set($type_number);
    }

    # base initialization done

    #! implicit assumption that this is a Chemesis3::Component, but can be overriden

    bless $self, $package;

    # apply constructor settings

    $self->settings($type, $chemesis3_mapping->{$type}->{constructor_settings});

    # apply user settings

    $self->settings($type, $settings);

    # return result

    return $self;
}


sub settings
{
    my $self = shift;

    my $type = shift;

    my $settings = shift;

    # just apply all the settings, the missing ones are under
    # default control of the C code

    foreach my $setting (keys %$settings)
    {
	# get target name in chemesis3 internal

	my $target = $setting;

	my $value = $settings->{$setting};

# 	if (ref $value eq 'HASH')
# 	{
# 	    no strict "refs";

# 	    my $Component = identifier_perl_to_xml($target);

# 	    my $constructor = "Chemesis3::${Component}::new";

# 	    $value = &$constructor($Component, $value);
# 	}

	# if there is a translator for this setting

	my $translator = $chemesis3_mapping->{$type}->{translators}->{$setting};

	if ($translator)
	{
	    # translate the target

	    $target = $translator->{target};

	    # translate the value

	    # for a custom value convertor

	    if ($translator->{convertor})
	    {
		# call custom value convertor

		my $convertor = $translator->{convertor};

		$value = &$convertor($target, $value);;
	    }

	    # for a simple source to target translator

	    #! so the constructor_settings entry applies this hook too,
	    #! and perhaps already created the object

	    elsif ($translator->{source})
	    {
		# if still needs translation

		if (!exists $value->{$translator->{source}})
		{
		    # get the factory method for the target object

		    my $source = $translator->{source};

		    my $factory_source = "Chemesis3::" . identifier_perl_to_xml($source);

		    # translate the source structure to a target object

		    $value = $factory_source->new($value);

		    # fetch the target object

		    $value = $value->{$source};
		}

		# else the constructor_settings has already constructed the target object

		else
		{
		    # fetch the target object

		    $value = $value->{$setting};
		}
	    }

	    # else

	    else
	    {
		# default is dereference via the setting name, which
		# presumably gives the chemesis3 internal structure

		$value = $value->{$setting};
	    }
	}

	# if there was a target

	if (defined $target)
	{
	    # set the chemesis3 internal target

	    my $subname = "swig_${target}_set";

	    $self->{$type}->$subname($value);
	}

	# else

	else
	{
	    # the convertor has done the necessary setting, or a void

	    #! see e.g. configuration, module_name and service_name for the chemesis3 entry

	    # but it is useful to keep the original

	    #! allows to set runtime configuration options

	    $self->{$setting} = $settings->{$setting};
	}
    }

    return $self;
}


sub identifier_xml_to_perl
{
    my $identifier = shift;

    my $result = $identifier;

    $result =~ s/([A-Z]{2,})([A-Z])/_\L$1\E$2/g;

    $result =~ s/([A-Z])(?![A-Z])/_\l$1/g;

    return $result;
}


sub identifier_perl_to_xml
{
    my $identifier = shift;

    my $result = $identifier;

    $result =~ s/^([a-z])/\u$1/;

    $result =~ s/_([a-z0-9])/\u$1/g;

    return $result;
}


# construct factory method for each Chemesis3 component

foreach my $component (keys %$chemesis3_mapping)
{
    my $Component = identifier_perl_to_xml($component);

#     print "For $component -> $Component\n";

    my $code = "
package Chemesis3::$Component;

sub new
{
    my \$package = shift;

    my \$result = Chemesis3::Component->new(\$package, '$component', \@_, );

    if (ref \$result)
    {
# 	print YAML::Dump('var1:', \$result, 'var2:', \$package);

	return bless \$result, \$package;
    }
    else
    {
	return \$result;
    }
}


sub chemesis3_object
{
    my \$self = shift;

    my \$result = \$self->{$component};

    return \$result;
}


sub backend
{
    my \$self = shift;

    my \$result = \$self->{$component};

    return \$result;
}


";

    my $result = eval $code;

    if ($@)
    {
	die "$0: In Chemesis3.pm: error constructing $component factory methods: $@";
    }
}


package Chemesis3::Dumper;


BEGIN { our @ISA = qw(Chemesis3::Glue); }


sub dump
{
    my $self = shift;

    my $ssp_analyzer = shift;

    my $options = shift;

    # lookup the object with the tables

    my $scheduler = $ssp_analyzer->{scheduler};

    # lookup the chemesis3

    my $solver = $scheduler->lookup_solver_engine($options->{source});

    if (!defined $solver)
    {
	die "$0: Chemesis3::Dumper::dump(): solver not found";
    }

    $self->{ssp_engine} = $solver;

    my $backend = $solver->backend();

    if (!$backend->isa("Chemesis3"))
    {
	die "$0: Chemesis3::Dumper::dump(): $backend is not a Chemesis3 object";
    }

    # get access to the low level C structure

    my $chemesis3 = $backend->backend();

    $self->{backend} = $backend;

    $backend->dump(@_);

    1;
}


sub new
{
    my $package = shift;

    my $options = shift || {};

    my $self
	= {
	   #! this gets called before Chemesis3 is instantiated so there
	   #! is no backend yet.

	   backend => undef,

	   %$options,
	  };

    bless $self, $package;

    return $self;
}


package Chemesis3::Glue;


sub backend
{
    my $self = shift;

    return $self->{backend};
}


package Chemesis3::Intermediary::Compiler;


BEGIN { our @ISA = qw(Chemesis3::Glue); }


sub load
{
    my $self = shift;

    my $ssp_service = shift;

    my $arguments = shift;

    my $intermediary = Chemesis3::Intermediary->new($arguments);

    $self->{backend} = $intermediary;

    my $result = defined $intermediary;

    return $result;
}


sub new
{
    my $package = shift;

    my $options = shift;

    my $self = { %$options, };

    bless $self, $package;

    return $self;
}


sub register_engine
{
    my $self = shift;

    my $engine = shift;

    my $modelname = shift;

    # do some concy checking for this restricted model container.

#     if (defined $modelname)
#     {
# 	return "$0: " . __PACKAGE__ . " cannot register_engine() for a named model ($modelname)";
#     }

#     if (!$engine->isa('Chemesis3::Intermediary::Compiler'))
#     {
# 	die "$0: register_engine() called for a object that is not a 'Chemesis3::Intermediary::Compiler' ($engine)";
#     }

    # return success

    return undef;
}


1;


